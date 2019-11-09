//
// Created by rick on 2019/11/9.
//

#define CATCH_CONFIG_MAIN

#include <QtCore>
#include <QtGui/QGuiApplication>
#include "./catch2/catch.hpp"
#include "../MusicPlayer/api/crypto.h"
#include "../MusicPlayer/api/api.h"
#include "../MusicPlayer/asyncfuture.h"

using namespace AsyncFuture;

TEST_CASE("djBanner", "[API]") {
  using namespace MusicPlayer::API;
  char *argv[] = {"test"};
  int argc = 1;
  QGuiApplication app{argc, argv};
  HttpWorker *worker = new HttpWorker;
  API *api = new API(worker);
  auto f = api->djBanner();
  observe(f).subscribe([](Response<APIDJBannersData> value) {
      std::visit([](const auto &v) {
          if constexpr (std::is_convertible_v<decltype(v), APIDJBannersData>) {
            qDebug() << v.data.size();
          } else {
            std::visit([](const auto &error) {
                qDebug() << "error";
            }, v);
          }
          qApp->quit();
      }, value);
      qDebug() << "success";
  });

  app.exec();
}

TEST_CASE("djCategoryExcludeHot", "[API]") {
  using namespace MusicPlayer::API;
  char *argv[] = {"test"};
  int argc = 1;
  QGuiApplication app{argc, argv};
  HttpWorker *worker = new HttpWorker;
  API *api = new API(worker);
  auto f = api->djCategoryExcludeHot();
  observe(f).subscribe([](Response<APIDJCategoryExcludeHotData> value) {
      std::visit([](const auto &v) {
          if constexpr (std::is_convertible_v<decltype(v), APIDJCategoryExcludeHotData>) {
            qDebug() << v.data.size();
            for (const auto &item : v.data) {
              qDebug() << item.name;
            }
          } else {
            std::visit([](const auto &error) {
                qDebug() << "error";
            }, v);
          }
          qApp->quit();
      }, value);
  });
  app.exec();
}

TEST_CASE("djCategoryRecommend", "[API]") {
  using namespace MusicPlayer::API;
  char *argv[] = {"test"};
  int argc = 1;
  QGuiApplication app{argc, argv};
  auto worker = new HttpWorker;
  auto api = new API(worker);
  auto f = api->djCategoryRecommend();
  observe(f).subscribe([](Response<APIDJCategoryRecommendData> value) {
      std::visit([](const auto &v) {
          if constexpr (std::is_convertible_v<decltype(v), APIDJCategoryRecommendData>) {
            qDebug() << v.data.size();
            for (const auto &item : v.data) {
              qDebug() << item.categoryName;
            }
          } else {
            std::visit([](const auto &error) {
                qDebug() << "error";
            }, v);
          }
          qApp->quit();
      }, value);
  });
  app.exec();
}
//}