//
// Created by rick on 2019/10/13.
//

#pragma once

#include <QtCore>
#include <QtNetwork>
#include <folly/futures/Future.h>
#include <optional>
#include <variant>
#include <vector>

namespace MusicPlayer::API {
    enum class HttpMethod { GET, POST, PUT };

    enum class CryptoType { WEAPI, LINUX_API, EAPI };

    enum class UserAgentType { Mobile, PC };

    struct RequestOption {
        CryptoType cryptoType                                                = CryptoType::WEAPI;
        std::optional<std::variant<QString, QHash<QString, QString>>> cookie = std::nullopt;
        std::optional<UserAgentType> ua                                      = std::nullopt;
    };

    class HttpWorker : public QObject {
        Q_OBJECT

        Q_DISABLE_COPY(HttpWorker)

        Q_ENUM(HttpMethod)

        HttpWorker();

      public:
        static void initInstance();

        static void freeInstance();

        static HttpWorker* instance();

        folly::SemiFuture<QNetworkReply*> post(QUrl&& url, RequestOption&& option, QVariantHash&& data);
        folly::SemiFuture<QNetworkReply*> get(QUrl&& url);

        bool event(QEvent* ev) override;

      private:
        void request(HttpMethod method,
                     QUrl&& url,
                     RequestOption&& option,
                     QVariantHash&& data,
                     folly::Promise<QNetworkReply*>&& promise);

        static HttpWorker* _instance;
        QNetworkAccessManager* _network;
    };

} // namespace MusicPlayer::API
Q_DECLARE_METATYPE(MusicPlayer::API::HttpMethod)
// Q_DECLARE_METATYPE(MusicPlayer::MusicAPI::HttpWorker)
