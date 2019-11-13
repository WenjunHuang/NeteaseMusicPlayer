//
// Created by rick on 2019/11/13.
//

#include "song_category_repository.h"
namespace MusicPlayer::Repository {
    SongCategoryRepository* SongCategoryRepository::_instance = nullptr;
    void SongCategoryRepository::initInstance() {
        if (!_instance)
            _instance = new SongCategoryRepository;
    }
    void SongCategoryRepository::freeInstance() {
        if (_instance) {
            _instance->deleteLater();
            _instance = nullptr;
        }
    }
    SongCategoryRepository* SongCategoryRepository::instance() {
        return _instance;
    }
}
