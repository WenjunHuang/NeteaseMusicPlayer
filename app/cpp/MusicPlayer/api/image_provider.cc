//
// Created by rick on 2020/2/7.
//

#include "image_provider.h"
#include "http.h"
#include "util.h"
#include <variant>
namespace MusicPlayer::API {
    class ImageResponsePrivate : public QQuickImageResponse {
      Q_OBJECT
      public:
        explicit ImageResponsePrivate(folly::SemiFuture<QNetworkReply*>&& future) {
            _future = std::move(future).via(Util::cpuExecutor()).thenValue([this](QNetworkReply* reply) {
              auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
              if (statusCode == 200 || statusCode == 304) {
                  setResultAndFinish(QImage::fromData(reply->readAll()));
              } else {
                  qDebug() << "failed to get image: " << reply->errorString();
                  setResultAndFinish(reply->errorString());
              }
              reply->deleteLater();
              return folly::unit;
            });
        }

        QQuickTextureFactory* textureFactory() const override {
            if (auto image = std::get_if<QImage>(&_result))
                return QQuickTextureFactory::textureFactoryForImage(*image);
            else
                return nullptr;
        }

        QString errorString() const override {
            if (auto error = std::get_if<QString>(&_result))
                return *error;
            else
                return QString();
        }


      private:
        folly::SemiFuture<folly::Unit> _future;
        std::variant<std::monostate, QString, QImage> _result;

        void setResultAndFinish(std::variant<QString, QImage> result) {
            std::visit(
                [this](auto& data) {
                  _result = data;
                  emit finished();
                },
                result);
        }
    };



    QQuickImageResponse* ImageProvider::requestImageResponse(const QString& id, const QSize& requestedSize) {
        qDebug() << "get image: " << id;
        auto httpWorker = HttpWorker::instance();
        return new ImageResponsePrivate(httpWorker->get(QUrl{id}));
    }
} // namespace MusicPlayer::API
#include "image_provider.moc"