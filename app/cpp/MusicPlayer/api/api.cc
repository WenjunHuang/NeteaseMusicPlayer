//
// Created by rick on 2019/11/7.
//

#include "api.h"
#include "../asyncfuture.h"
#include <QDebug>

namespace MusicPlayer::API {
    APIResponse<APIDJBannersData> API::djBanner() {
      QUrl url("https://music.163.com/weapi/djradio/banner/get");
      auto response = _httpWorker->post(url, {
        CryptoType::WEAPI,
        {QHash<QString, QString>{{"os", "pc"}}}
      }, {});

      return AsyncFuture::observe(response).subscribe([this](QNetworkReply *reply) {
          return parseResponse<APIDJBannersData>(reply);
      }).future();
    }

    APIResponse<APIDJCategoryExcludeHotData> API::djCategoryExcludeHot() {
      QUrl url("https://music.163.com/weapi/djradio/category/excludehot");
      auto response = _httpWorker->post(url, {
        CryptoType::WEAPI,
        {}
      }, {});
      return AsyncFuture::observe(response).subscribe([this](QNetworkReply *reply) {
          return parseResponse<APIDJCategoryExcludeHotData>(reply);
      }).future();
    }

    APIResponse<APIDJCategoryRecommendData> API::djCategoryRecommend() {
      QUrl url("https://music.163.com/weapi/djradio/home/category/recommend");
      auto response = _httpWorker->post(url, {
        CryptoType::WEAPI,
        {}
      }, {});
      return AsyncFuture::observe(response).subscribe([this](QNetworkReply *reply) {
          return parseResponse<APIDJCategoryRecommendData>(reply);
      }).future();
    }
}
