//
// Created by rick on 2019/11/7.
//

#pragma once
#include "data/error.h"
#include "http.h"
#include <QFuture>
#include <QJsonDocument>
#include <exception>
#include <variant>

namespace MusicPlayer::API {
    class API {
      public:
        explicit API(HttpWorker* httpWorker) { _httpWorker = httpWorker; }

      private:
        template <typename T> using ParseResponse = std::variant<APIError, T>;
        template <typename T>
        ParseResponse<T> parseResponse(QNetworkReply* reply) {
            //            QFutureInterface<ParseResponse<T>> promise(
            //                QFutureInterfaceBase::Running);

            auto statusCode =
                reply->attribute(QNetworkRequest::HttpStatusCodeAttribute)
                    .toInt();
            if (statusCode == 200) {
                QJsonParseError jsonError;
                auto document =
                    QJsonDocument::fromJson(reply->readAll(), &jsonError);
                return T::fromJsonValue(document.object());
            } else {

            }
        }

      private:
        HttpWorker* _httpWorker;
    };
} // namespace MusicPlayer::API
