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
#include <vector>

namespace MusicPlayer::API {
    enum class HttpMethod {
        GET,
        POST,
        PUT
    };

    enum class CryptoType {
        WEAPI,
        LINUX_API,
        EAPI
    };

    enum class UserAgentType {
        Mobile,
        PC
    };

    struct RequestOption {
        CryptoType cryptoType;
        std::optional<std::variant<QString, QHash<QString, QString>>> cookie = std::nullopt;
        std::optional<UserAgentType> ua = std::nullopt;
    };


    class HttpWorker : public QObject {
    Q_OBJECT

        Q_ENUM(HttpMethod)

    public:
        explicit HttpWorker(QObject *parent = nullptr);

        QFuture<QNetworkReply *> post(QUrl url,
                                      RequestOption option,
                                      const QHash<QString,QVariant>& data);

    signals:

        // this signal is used internally
        void _request(HttpMethod method,
                      QUrl url,
                      RequestOption option,
                      QHash<QString,QVariant> data,
                      QFutureInterface<QNetworkReply *> futureItr);

    private:
        QThread *_worker;
        QNetworkAccessManager *_network;
    };
}
Q_DECLARE_METATYPE(MusicPlayer::API::HttpMethod)
//Q_DECLARE_METATYPE(MusicPlayer::API::HttpWorker)
