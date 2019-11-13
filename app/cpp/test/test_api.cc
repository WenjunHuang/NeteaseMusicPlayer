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

TEST_CASE("djBanner", "[MusicAPI]") {
  using namespace MusicPlayer::API;
  char *argv[] = {"test"};
  int argc = 1;
  QGuiApplication app{argc, argv};
  HttpWorker::initInstance();
  MusicAPI api;
  auto f = api.djBanner();
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

TEST_CASE("djCategoryExcludeHot", "[MusicAPI]") {
  using namespace MusicPlayer::API;
  char *argv[] = {"test"};
  int argc = 1;
  QGuiApplication app{argc, argv};
  HttpWorker::initInstance();
  MusicAPI api;
  auto f = api.djCategoryExcludeHot();
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

TEST_CASE("banner", "[MusicAPI]") {
  using namespace MusicPlayer::API;
  char *argv[] = {"test"};
  int argc = 1;
  QGuiApplication app{argc, argv};
  HttpWorker::initInstance();
  MusicAPI api;
  auto f = api.banner();
  observe(f).subscribe([](Response<APIBannersData> value) {
      std::visit([](const auto &v) {
          if constexpr (std::is_convertible_v<decltype(v), APIBannersData>) {
            qDebug() << v.banners.size();
            for (const auto &item : v.banners) {
              qDebug() << item.imageUrl;
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

TEST_CASE("personalized_newsong", "[MusicAPI]") {
  using namespace MusicPlayer::API;
  char *argv[] = {"test"};
  int argc = 1;
  QGuiApplication app{argc, argv};
  HttpWorker::initInstance();
  MusicAPI api;
  auto f = api.personalizedNewSong();
  observe(f).subscribe([](Response<APIPersonalizedNewSongData> value) {
      std::visit([](const auto &v) {
          if constexpr (std::is_convertible_v<decltype(v), APIPersonalizedNewSongData>) {
            qDebug() << v.result.size();
            for (const auto &item : v.result) {
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

TEST_CASE("djCategoryRecommend", "[MusicAPI]") {
  using namespace MusicPlayer::API;
  char *argv[] = {"test"};
  int argc = 1;
  QGuiApplication app{argc, argv};
  HttpWorker::initInstance();
  MusicAPI api;
  auto f = api.djCategoryRecommend();
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

TEST_CASE("personalized", "[MusicAPI]") {
  using namespace MusicPlayer::API;
  char *argv[] = {"test"};
  int argc = 1;
  QGuiApplication app{argc, argv};
  HttpWorker::initInstance();
  MusicAPI api;
  auto f = api.personalized();
  observe(f).subscribe([](Response<APIPersonalizedData> value) {
      std::visit([](const auto &v) {
          if constexpr (std::is_convertible_v<decltype(v), APIPersonalizedData>) {
            qDebug() << v.result.size();
            for (const auto &item : v.result) {
              qDebug() << item.name << " " << item.picUrl;
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

TEST_CASE("loginCellphone", "[MusicAPI]") {
    using namespace MusicPlayer::API;
    char *argv[] = {"test"};
    int argc = 1;
    QGuiApplication app{argc, argv};
    HttpWorker::initInstance();
    MusicAPI api;
    auto f = api.loginCellphone("18027190235","Rick198023");
    observe(f).subscribe([](Response<APIUserLoginData> value) {
      std::visit([](const auto &v) {
        if constexpr (std::is_convertible_v<decltype(v), APIUserLoginData>) {
            if (v.cookieToken)
                qDebug() << v.cookieToken.value();
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

TEST_CASE("userPrivateMessages", "[MusicAPI]") {
    using namespace MusicPlayer::API;
    char *argv[] = {"test"};
    int argc = 1;
    QGuiApplication app{argc, argv};
    HttpWorker::initInstance();
    MusicAPI api;
    auto f = api.userPrivateMessages("; MUSIC_U=32506ca1e2f682f81fb7fe6a0ebf3c746125db7247d6651fd053861143761ee3053a3c2009db5a182cd526183697c5bcfe2897047e8106fb; __csrf=0b15c1aee3089531a9e5575b5053c104");
    observe(f).subscribe([](Response<APIUserPrivateMessagesData> value) {
      std::visit([](const auto &v) {
        if constexpr (std::is_convertible_v<decltype(v), APIUserPrivateMessagesData>) {
                qDebug() << v.newMsgCount;
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

TEST_CASE("playlistCatlist", "[MusicAPI]") {
    using namespace MusicPlayer::API;
    char *argv[] = {"test"};
    int argc = 1;
    QGuiApplication app{argc, argv};
    HttpWorker::initInstance();
    MusicAPI api;
    auto f = api.playlistCatlist();
    observe(f).subscribe([](Response<APIPlaylistCatListData> value) {
      std::visit([](const auto &v) {
        if constexpr (std::is_convertible_v<decltype(v), APIPlaylistCatListData>) {
            qDebug() << v.all.name;
            qDebug() << v.sub.size();
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