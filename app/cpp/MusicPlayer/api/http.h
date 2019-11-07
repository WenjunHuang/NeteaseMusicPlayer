//
// Created by rick on 2019/10/13.
//

#pragma once

#include <QFutureInterface>
#include <QThread>
#include <QtCore/QFuture>
#include <QtCore/QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

namespace MusicPlayer::API {
    enum class HttpMethod {
        GET,
        POST,
        PUT,
    };
    class HttpWorker : public QObject {
        Q_OBJECT
        Q_ENUM(HttpMethod)
      public:
        explicit HttpWorker(QObject* parent = nullptr)
            : QObject{parent}, _network{new QNetworkAccessManager} {

            _worker = new QThread;
            _worker->setObjectName("HttpWorker");
            _network->moveToThread(_worker);
            moveToThread(_worker);

            connect(this, &HttpWorker::request, this,
                    [this](HttpMethod method, const QNetworkRequest& request,
                           const QByteArray& content,
                           QFutureInterface<QNetworkReply*> result) {
                        QNetworkReply* reply = nullptr;

                        if (method == HttpMethod::GET)
                            reply = _network->get(request);
                        else if (method == HttpMethod::POST)
                            reply = _network->post(request, content);

                        QObject::connect(reply, &QNetworkReply::finished,
                                         [reply, result]() mutable {
                                             result.reportFinished(&reply);
                                         });
                    });
            _worker->start();
        }

        QFuture<QNetworkReply*> get(const QNetworkRequest& networkRequest) {
            QFutureInterface<QNetworkReply*> promise(
                QFutureInterfaceBase::Running);

            emit request(HttpMethod::GET, networkRequest, QByteArray(),
                         promise);

            return promise.future();
        }

        QFuture<QNetworkReply*> post(const QNetworkRequest& networkRequest,
                                     const QByteArray& content) {
            QFutureInterface<QNetworkReply*> promise(
                QFutureInterfaceBase::Running);

            emit request(HttpMethod::POST, networkRequest, content, promise);
        }

      signals:
        // this signal is used internally
        void request(HttpMethod method, QNetworkRequest request,
                     QByteArray content,
                     QFutureInterface<QNetworkReply*> futureItr);

      private:
        QThread* _worker;
        QNetworkAccessManager* _network;
    };
}
Q_DECLARE_METATYPE(MusicPlayer::API::HttpMethod)
Q_DECLARE_METATYPE(MusicPlayer::API::HttpWorker)
