//
// Created by rick on 2019/11/7.
//

#include "api.h"
#include "../asyncfuture.h"
#include <QDebug>

namespace MusicPlayer::API {
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
    }

    APIResponse<APIDJBannersData> MusicAPI::djBanner() {
      QUrl url("https://music.163.com/weapi/djradio/banner/get");
      auto response = HttpWorker::instance()->post(url, {
        CryptoType::WEAPI,
        {QHash<QString, QString>{{"os", "pc"}}}
      }, {});

      return AsyncFuture::observe(response).subscribe([this](QNetworkReply *reply) {
          return parseResponse<APIDJBannersData>(reply);
      }).future();
    }

    APIResponse<APIDJCategoryExcludeHotData> MusicAPI::djCategoryExcludeHot() {
      QUrl url("https://music.163.com/weapi/djradio/category/excludehot");
      auto response = HttpWorker::instance()->post(url, {
        CryptoType::WEAPI,
        {}
      }, {});
      return AsyncFuture::observe(response).subscribe([this](QNetworkReply *reply) {
          return parseResponse<APIDJCategoryExcludeHotData>(reply);
      }).future();
    }

    APIResponse<APIDJCategoryRecommendData> MusicAPI::djCategoryRecommend() {
      QUrl url("https://music.163.com/weapi/djradio/home/category/recommend");
      auto response = HttpWorker::instance()->post(url, {
        CryptoType::WEAPI,
        {}
      }, {});
      return AsyncFuture::observe(response).subscribe([this](QNetworkReply *reply) {
          return parseResponse<APIDJCategoryRecommendData>(reply);
      }).future();
    }

    APIResponse<APIBannersData> MusicAPI::banner() {
      QUrl url("https://music.163.com/api/v2/banner/get");
      auto response = HttpWorker::instance()->post(url, {
        CryptoType::LINUX_API,
        {}
      }, {{"clientType", "pc"}});
      return AsyncFuture::observe(response).subscribe([this](QNetworkReply *reply) {
          return parseResponse<APIBannersData>(reply);
      }).future();
    }

    APIResponse<APIPersonalizedNewSongData> MusicAPI::personalizedNewSong() {
      QUrl url("https://music.163.com/weapi/personalized/newsong");
      auto response = HttpWorker::instance()->post(url, {
        CryptoType::WEAPI,
        {}
      }, {{"type", "recommend"}});
      return AsyncFuture::observe(response).subscribe([this](QNetworkReply *reply) {
          return parseResponse<APIPersonalizedNewSongData>(reply);
      }).future();
    }

    APIResponse<APIPersonalizedData> MusicAPI::personalized(int limit) {
      QUrl url("https://music.163.com/weapi/personalized/playlist");
      auto response = HttpWorker::instance()->post(url, {
        CryptoType::WEAPI,
        {}
      }, {{"limit", limit},
          {"total", true},
          {"n",     1000}});
      return AsyncFuture::observe(response).subscribe([this](QNetworkReply *reply) {
          return parseResponse<APIPersonalizedData>(reply);
      }).future();
    }

}
