//
// Created by rick on 2020/2/7.
//

#include "image_provider.h"
#include "http.h"
#include "repository.h"
#include "util.h"
#include <QNetworkReply>
#include <QtConcurrent/QtConcurrent>
#include <chrono>
#include <filesystem>
#include <variant>

namespace MusicPlayer::API {
    using namespace Repository;
    using namespace Util;
    class ImageResponsePrivate : public QQuickImageResponse {
        Q_OBJECT
      public:
        explicit ImageResponsePrivate(const QString& url) {
            auto httpWorker = MusicHttpWorker::instance();
            auto database   = DatabaseRepository::instance();
            auto appConfig  = AppConfig::instance();
            auto handler    = database->getImageCacheByUrl(url);
            connect(handler,
                    &DatabaseResponseHandler<std::optional<TImageCache>>::finished,
                    [this, httpWorker, appConfig, database, url = url](
                        const DatabaseResponse<std::optional<TImageCache>>& response) {
                        std::visit(
                            [=](auto const& cache) {
                                if constexpr (std::is_convertible_v<decltype(cache), std::optional<TImageCache>>) {
                                    if (cache.has_value()) {
                                        auto validTill = QDateTime::fromMSecsSinceEpoch(cache.value().validTill);
                                        auto now       = QDateTime::currentDateTime();
                                        if (validTill < now) {
                                            // cache已经失效
                                        } else {
                                            QString cacheFile{(appConfig->imageCacheDir() / cache.value().path)
                                                                  .lexically_normal()
                                                                  .string()
                                                                  .data()};
                                            QFile file{cacheFile};
                                            file.open(QIODevice::ReadOnly);
                                            auto fileContent = file.readAll();
                                            setResultAndFinish(QImage::fromData(fileContent));
                                        }
                                    } else {
                                        auto httpHandler = httpWorker->get(url);
                                        connect(httpHandler, &MusicHttpHandler::finished, [=](MusicHttpResult const& result) {
                                            if (result.errorString.isEmpty()) {
                                                QtConcurrent::run([=, result = result]() {
                                                    QUuid uuid = QUuid::createUuid();
                                                    QString cacheFile{(appConfig->imageCacheDir() /
                                                                       uuid.toString(QUuid::WithoutBraces).toStdString())
                                                                          .lexically_normal()
                                                                          .string()
                                                                          .data()};
                                                    QFile file{cacheFile};
                                                    file.open(QIODevice::WriteOnly);
                                                    file.write(result.data);
                                                    file.flush();

                                                    database->insertImageCache(
                                                        TImageCache{-1,
                                                                    url.toStdString(),
                                                                    cacheFile.toStdString(),
                                                                    cacheFile.toStdString(),
                                                                    QDateTime::currentDateTime().addDays(7).toMSecsSinceEpoch(),
                                                                    QDateTime::currentDateTime().toMSecsSinceEpoch()});

                                                    setResultAndFinish(QImage::fromData(result.data));
                                                });
                                            }
                                        });
                                    }
                                }
                            },
                            response);

                        //            _future = std::move(future).via(Util::cpuExecutor()).thenValue([this](QNetworkReply*
                        //            reply) {
                        //                auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
                        //                if (statusCode == 200 || statusCode == 304) {
                        //                    setResultAndFinish(QImage::fromData(reply->readAll()));
                        //                } else {
                        //                    qDebug() << "failed to get image: " << reply->errorString();
                        //                    setResultAndFinish(reply->errorString());
                        //                }
                        //                reply->deleteLater();
                        //                return folly::unit;
                        //            });
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
        return new ImageResponsePrivate(id);
    }
} // namespace MusicPlayer::API
#include "image_provider.moc"