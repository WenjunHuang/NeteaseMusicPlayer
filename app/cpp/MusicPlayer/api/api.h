//
// Created by rick on 2019/11/7.
//

#pragma once

#include "data/error.h"
#include "http.h"
#include "data/dj_banner.h"
#include "data/dj_category_excludehot.h"
#include "data/dj_category_recommend.h"
#include <QFuture>
#include <QJsonDocument>
#include <QtConcurrent>
#include <QFutureWatcher>
#include <exception>
#include <variant>

namespace MusicPlayer::API {
    template<typename T> using Response = std::variant<Error, T>;
    template<typename T> using APIResponse = QFuture<Response<T>>;

    class API {
    public:

        explicit API(HttpWorker *httpWorker) {
          _httpWorker = httpWorker;
          qRegisterMetaType<HttpMethod>("HttpMethod");
          qRegisterMetaType<RequestOption>("RequestOption");
          qRegisterMetaType<QFutureInterface<QNetworkReply *>>("QFutureInterface<QNetworkReply*>");
        }

        APIResponse<APIDJBannersData> djBanner();

        APIResponse<APIDJCategoryExcludeHotData> djCategoryExcludeHot();

        APIResponse<APIDJCategoryRecommendData> djCategoryRecommend();


    private:
        template<typename T>
        APIResponse<T> parseResponse(QNetworkReply *reply) {
          auto fun = [reply]() {
              auto statusCode =
                reply->attribute(QNetworkRequest::HttpStatusCodeAttribute)
                  .toInt();
              if (statusCode == 200) {
                QJsonParseError jsonError;
                auto document =
                  QJsonDocument::fromJson(reply->readAll(), &jsonError);
                if (jsonError.error != QJsonParseError::NoError)
                  return Response<T>{std::in_place_index<0>, JsonFormatError{jsonError}};
                return Response<T>{std::in_place_index<1>, T::fromJsonValue(document.object())};
              } else {
                return Response<T>(std::in_place_index<0>, NetworkError{reply->errorString()});
              }
          };
          return QtConcurrent::run(fun);
//          return fun();
        }

    private:
        HttpWorker *_httpWorker;
    };
} // namespace MusicPlayer::API
