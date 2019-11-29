//
// Created by rick on 2019/11/9.
//

#include "../MusicPlayer/api/api.h"
#include "../MusicPlayer/api/crypto.h"
#include "../MusicPlayer/api/data/data.h"
#include "../MusicPlayer/util/executor.h"
#include "set_up.h"
#include "./catch2/catch.hpp"
#include <QtCore>
#include <QtGui/QGuiApplication>
#include <iostream>

using namespace MusicPlayer::API;
using namespace MusicPlayer::Util;

TEST_CASE("djBanner", "[MusicAPI]") {
    auto app = setUp();

    MusicAPI api;
    auto f = api.djBanner();
    std::move(f).via(AppExecutor::instance()->getMainExecutor().get()).thenValue([](Response<APIDJBannersData> value) {
        auto threadId = std::this_thread::get_id();
        std::cout << "thenValue:" << threadId << std::endl;

        std::visit(
            [](const auto& v) {
                if constexpr (std::is_convertible_v<decltype(v), APIDJBannersData>) {
                    qDebug() << v.data.size();
                    for (const auto& data : v.data) {
                        qDebug() << data.template value<APIDJBannerData>().url;
                    }
                } else {
                    std::visit([](const auto& error) { qDebug() << "error"; }, v);
                }
                qApp->quit();
            },
            value);
        qDebug() << "success";
    });

    app->exec();
}

TEST_CASE("djCategoryExcludeHot", "[MusicAPI]") {
    auto app = setUp();
    MusicAPI api;
    auto f = api.djCategoryExcludeHot();
    std::move(f)
        .via(AppExecutor::instance()->getMainExecutor().get())
        .thenValue([](Response<APIDJCategoryExcludeHotData> value) {
            std::visit(
                [](const auto& v) {
                    if constexpr (std::is_convertible_v<decltype(v), APIDJCategoryExcludeHotData>) {
                        qDebug() << v.data.size();
                        for (const auto& item : v.data) {
                            qDebug() << item.template value<APIDJCategoryItemData>().name;
                        }
                    } else {
                        std::visit([](const auto& error) { qDebug() << "error"; }, v);
                    }
                    qApp->quit();
                },
                value);
        });
    app->exec();
}

TEST_CASE("banner", "[MusicAPI]") {
    auto app = setUp();
    MusicAPI api;
    api.banner().via(mainExecutor()).thenValue([](const Response<APIBannersData>& value) {
        std::visit(
            [](const auto& v) {
                if constexpr (std::is_convertible_v<decltype(v), APIBannersData>) {
                    qDebug() << v.banners.size();
                    for (const auto& item : v.banners) {
                        qDebug() << item.template value<APIBannerData>().imageUrl;
                    }
                } else {
                    std::visit([](const auto& error) { qDebug() << "error"; }, v);
                }
                qApp->quit();
            },
            value);
    });
    app->exec();
}
//
TEST_CASE("personalized_newsong", "[MusicAPI]") {
    auto app = setUp();
    MusicAPI api;
    api.personalizedNewSong().via(mainExecutor()).thenValue([](const Response<APIPersonalizedNewSongData>& value) {
        std::visit(
            [](const auto& v) {
                if constexpr (std::is_convertible_v<decltype(v), APIPersonalizedNewSongData>) {
                    qDebug() << v.result.size();
                    for (const auto& item : v.result) {
                        qDebug() << item.template value<APIPersonalizedNewSongResultData>().name;
                    }
                } else {
                    std::visit([](const auto& error) { qDebug() << "error"; }, v);
                }
                qApp->quit();
            },
            value);
    });
    app->exec();
}

TEST_CASE("djCategoryRecommend", "[MusicAPI]") {
    auto app = setUp();
    MusicAPI api;
    api.djCategoryRecommend().via(mainExecutor()).thenValue([](const Response<APIDJCategoryRecommendData>& value) {
        std::visit(
            [](const auto& v) {
                if constexpr (std::is_convertible_v<decltype(v), APIDJCategoryRecommendData>) {
                    qDebug() << v.data.size();
                    for (const auto& item : v.data) {
                        qDebug() << item.template value<APIDJCategoryRecommendItemData>().categoryName;
                    }
                } else {
                    std::visit([](const auto& error) { qDebug() << "error"; }, v);
                }
                qApp->quit();
            },
            value);
    });
    app->exec();
}
//
TEST_CASE("personalized", "[MusicAPI]") {
    auto app = setUp();
    MusicAPI api;
    api.personalized().via(mainExecutor()).thenValue([](const Response<APIPersonalizedData>& value) {
        std::visit(
            [](const auto& v) {
                if constexpr (std::is_convertible_v<decltype(v), APIPersonalizedData>) {
                    qDebug() << v.result.size();
                    for (const auto& item : v.result) {
                        auto value = item.template value<APIPersonalizedItemData>();
                        qDebug() << value.name << " " << value.picUrl;
                    }
                } else {
                    std::visit([](const auto& error) { qDebug() << "error"; }, v);
                }
                qApp->quit();
            },
            value);
    });
    app->exec();
}
//
// TEST_CASE("loginCellphone", "[MusicAPI]") {
//    using namespace MusicPlayer::API;
//    char *argv[] = {"test"};
//    int argc = 1;
//    QGuiApplication app{argc, argv};
//    HttpWorker::initInstance();
//    MusicAPI api;
//    auto f = api.loginCellphone("18027190235","Rick198023");
//    observe(f).subscribe([](Response<APIUserLoginData> value) {
//      std::visit([](const auto &v) {
//        if constexpr (std::is_convertible_v<decltype(v), APIUserLoginData>) {
//            if (v.cookieToken)
//                qDebug() << v.cookieToken.value();
//        } else {
//            std::visit([](const auto &error) {
//              qDebug() << "error";
//            }, v);
//        }
//        qApp->quit();
//      }, value);
//    });
//    app.exec();
//}
//
// TEST_CASE("userPrivateMessages", "[MusicAPI]") {
//    using namespace MusicPlayer::API;
//    char *argv[] = {"test"};
//    int argc = 1;
//    QGuiApplication app{argc, argv};
//    HttpWorker::initInstance();
//    MusicAPI api;
//    auto f = api.userPrivateMessages(";
//    MUSIC_U=32506ca1e2f682f81fb7fe6a0ebf3c746125db7247d6651fd053861143761ee3053a3c2009db5a182cd526183697c5bcfe2897047e8106fb;
//    __csrf=0b15c1aee3089531a9e5575b5053c104"); observe(f).subscribe([](Response<APIUserPrivateMessagesData> value) {
//      std::visit([](const auto &v) {
//        if constexpr (std::is_convertible_v<decltype(v), APIUserPrivateMessagesData>) {
//                qDebug() << v.newMsgCount;
//        } else {
//            std::visit([](const auto &error) {
//              qDebug() << "error";
//            }, v);
//        }
//        qApp->quit();
//      }, value);
//    });
//    app.exec();
//}
//
TEST_CASE("playlistCatlist", "[MusicAPI]") {
    auto app = setUp();
    MusicAPI api;
    api.playlistCatlist().via(mainExecutor()).thenValue([](const Response<APIPlaylistCatListData>& value) {
        std::visit(
            [](const auto& v) {
                if constexpr (std::is_convertible_v<decltype(v), APIPlaylistCatListData>) {
                    qDebug() << v.all.name;

                    for (auto itr = v.categories.cbegin(); itr != v.categories.cend(); itr++) {
                        auto key   = itr.key();
                        auto value = itr.value().toString();
                        qDebug() << key << ":" << value;
                    }

                    // items
                    qDebug() << "sub count:" << v.sub.size();
                    for (auto itr = v.sub.cbegin(); itr != v.sub.cend(); itr++) {
                        auto subItem = (*itr).template value<APIPlaylistCatListItemData>();
                        qDebug() << subItem.category << ":" << subItem.name;
                    }
                } else {
                    std::visit([](const auto& error) { qDebug() << "error"; }, v);
                }
                qApp->quit();
            },
            value);
    });
    app->exec();
}
////}