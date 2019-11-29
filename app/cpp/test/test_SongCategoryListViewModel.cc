//
// Created by HUANG WEN JUN on 2019/11/29.
//
#include "../MusicPlayer/view_models/song_category_list_view_model.h"
#include "./catch2/catch.hpp"
#include "set_up.h"
#include <QtCore>
#include <QtGui/QGuiApplication>
#include <iostream>

TEST_CASE("song_category_list_view_model", "[ViewModels]") {
    using namespace MusicPlayer::ViewModels;
    auto app                             = setUp();
    SongCategoryListViewModel* viewModel = new SongCategoryListViewModel;
    REQUIRE(viewModel->state().canConvert<UnInitState>() == true);

    int loadTime = 0;
    QObject::connect(viewModel, &SongCategoryListViewModel::stateChanged, [&]() {
        if (viewModel->state().canConvert<LoadingState>())
            qDebug() << "loading";
        else {
            if (viewModel->state().canConvert<ReadyState>()) {
                qDebug() << "ready";

                auto ready = viewModel->state().value<ReadyState>();

                qDebug() << ready.allName;

                for (const auto& itr : ready.items) {
                    auto item = itr.value<ReadyStateItem>();
                    qDebug() << "  " << item.name;
                    QStringList subNames;
                    for (const auto& subItr : item.subCats) {
                        auto subItem = subItr.value<APIPlaylistCatListItemData>();
                        subNames.append(subItem.name);
                    }
                    qDebug() << "    " << subNames.join(',');
                }

                // load a second time
                if (loadTime < 1) {
                    loadTime++;
                    viewModel->reload();
                }
                else
                    app->quit();
            }
            if (viewModel->state().canConvert<ErrorState>()) {
                qDebug() << "error:" << viewModel->state().value<ErrorState>().message;

                app->quit();
            }
        }
    });

    viewModel->reload();
    viewModel->reload();

    app->exec();
}
