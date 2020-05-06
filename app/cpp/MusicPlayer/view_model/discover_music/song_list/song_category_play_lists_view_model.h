//
// Created by HUANG WEN JUN on 2019/12/3.
//

#pragma once
#include "../../base_state_view_model.h"
#include "../../states.h"
#include <QtCore>
#include <optional>
#include <atomic>
namespace MusicPlayer::ViewModel {

    class SongCategoryPlayListsViewModel : public BaseStateViewModel {
        Q_OBJECT
      public:
        enum class CreatorType { Normal, Expert, Musician, Official };
        Q_ENUM(CreatorType)

        explicit SongCategoryPlayListsViewModel(QObject* parent = nullptr) : BaseStateViewModel{parent} {}

        Q_INVOKABLE void load(const QString& catName, int limit, int offset);

        static void registerMetaTypes();
    };

    struct SongCategoryPlayListsViewModelReadyStateData {
        Q_GADGET
        Q_PROPERTY(QVariantList playlist MEMBER playlist)
        Q_PROPERTY(int total MEMBER total)

      public:
        QVariantList playlist;
        int total;
    };

    struct SongCategoryPlayListsViewModelPlaylistItem {
        Q_GADGET
        Q_PROPERTY(int playlistId MEMBER playlistId)
        Q_PROPERTY(QUrl coverImgUrl MEMBER coverImgUrl)
        Q_PROPERTY(QString name MEMBER name)
        Q_PROPERTY(int playCount MEMBER playCount)
        Q_PROPERTY(QString creatorName MEMBER creatorName)
        Q_PROPERTY(MusicPlayer::ViewModel::SongCategoryPlayListsViewModel::CreatorType creatorType MEMBER creatorType)
      public:
        int playlistId;
        QUrl coverImgUrl;
        QString name;
        int playCount;
        QString creatorName;
        SongCategoryPlayListsViewModel::CreatorType creatorType;
    };
} // namespace MusicPlayer::ViewModels

Q_DECLARE_METATYPE(MusicPlayer::ViewModel::SongCategoryPlayListsViewModelPlaylistItem)
Q_DECLARE_METATYPE(MusicPlayer::ViewModel::SongCategoryPlayListsViewModelReadyStateData)
