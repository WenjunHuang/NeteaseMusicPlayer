//
// Created by rick on 2020/3/22.
//

#include "app_config.h"
namespace MusicPlayer::Repository{
    AppConfig* AppConfig::instance_ = nullptr;

    AppConfig::AppConfig() {}

    void AppConfig::initInstance() {
        if (!instance_) {
            instance_ = new AppConfig();
        }
    }

    void AppConfig::freeInstance() {
        if (instance_) {
            delete instance_;
            instance_ = nullptr;
        }
    }

    AppConfig* AppConfig::instance() {
        return instance_;
    }

    fs::path AppConfig::imageCacheDir() const {
        return fs::path(".");
    }

}
