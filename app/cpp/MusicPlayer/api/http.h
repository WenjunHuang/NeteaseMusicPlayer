//
// Created by rick on 2019/10/13.
//

#pragma once

#include <QtCore>
#include <QtNetwork>
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

    struct MusicHttpResult {
        QString url;
        QString errorString;
        QByteArray data;
        QNetworkReply *reply;
    };

    class MusicHttpWorker;

    class MusicHttpHandler : public QObject {
        Q_OBJECT
        Q_DISABLE_COPY(MusicHttpHandler)
        friend class MusicHttpWorker;

      public:
        explicit MusicHttpHandler(const QString& url);

        void cancel();
      signals:
        void finished(MusicHttpResult const &result);

      private:
        void attachNetworkReply(QNetworkReply* reply);

        QNetworkReply* reply_ = nullptr;
        QString url_;
    };

    class MusicHttpWorker : public QObject {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(MusicHttpWorker)

        Q_ENUM(HttpMethod)

        MusicHttpWorker();

      public:
        static void initInstance();

        static void freeInstance();

        static MusicHttpWorker* instance();

        MusicHttpHandler* post(QUrl&& url, RequestOption&& option, QVariantHash&& data);
        MusicHttpHandler* get(QUrl&& url);

        bool event(QEvent* ev) override;

      private:
        void request(HttpMethod method,
                     QUrl&& url,
                     RequestOption&& option,
                     QVariantHash&& data,
                     MusicHttpHandler* handler);

        static MusicHttpWorker* _instance;
        QNetworkAccessManager* _network;
    };

} // namespace MusicPlayer::API
Q_DECLARE_METATYPE(MusicPlayer::API::HttpMethod)
Q_DECLARE_METATYPE(MusicPlayer::API::MusicHttpResult)
