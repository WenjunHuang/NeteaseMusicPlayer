//
// Created by HUANG WEN JUN on 2020/5/6.
//
#include <QtCore/QtCore>
#include "repository.h"

namespace MusicPlayer::Repository {
    void registerMetaTypes() {
        qRegisterMetaType<DatabaseResponse<int>>("DatabaseResponse<int>");
        qRegisterMetaType<DatabaseResponse<std::optional<TImageCache>>>("DatabaseResponse<std::optional<TImageCache>>");
        qRegisterMetaType<DatabaseResponse<QVector<TImageCache>>>("DatabaseResponse<QVector<TImageCache>>");
        qRegisterMetaType<DatabaseResponse<QVector<TPlayListSong>>>("DatabaseResponse<QVector<TPlayListSong>>");
    }

    void initRepositoryModule() {
        registerMetaTypes();

        AppConfig::initInstance();
        DatabaseRepository::initInstance();
    }

}