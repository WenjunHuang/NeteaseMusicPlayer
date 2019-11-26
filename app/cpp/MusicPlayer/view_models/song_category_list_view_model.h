//
// Created by rick on 2019/11/13.
//

#pragma once
#include "../api/api.h"
#include "../asyncfuture.h"
#include <QVariantHash>
#include <QtCore/QObject>
#include <QtQml/QQmlParserStatus>

namespace MusicPlayer::ViewModels {
    using namespace MusicPlayer::API;
    enum class StateKind {
        Loading,
        Ready
    };

    struct LoadingState {
        Q_GADGET
        Q_PROPERTY(StateKind kind READ kind)
      public:
        StateKind kind() const {
            return StateKind::Loading;
        }
    };

    struct ReadyStateItem {
        Q_GADGET
        Q_PROPERTY(QString name MEMBER name)
        Q_PROPERTY(QString icon MEMBER icon)
        Q_PROPERTY(QVariantList catItems MEMBER catItems)
      public:
        QString name;
        QString icon;
        QVariantList catItems;//APIPlaylistCatListItemData
    };

    struct ReadyState {
        Q_GADGET
        Q_PROPERTY(StateKind kind READ kind)
      public:
        QVariantHash data;
        StateKind kind() const {
            return StateKind::Ready;
        }
    };


    class SongCategoryListViewModel : public QObject, public QQmlParserStatus {
        Q_OBJECT
        Q_INTERFACES(QQmlParserStatus)
        Q_ENUM(StateKind)
      public:
        explicit SongCategoryListViewModel(QObject* parent = nullptr)
            : QObject(parent),_state{LoadingState()} {}

        ~SongCategoryListViewModel() = default;

        void classBegin() override {}

        void componentComplete() override {
            MusicAPI api;
            auto f = api.playlistCatlist();

            AsyncFuture::observe(f).subscribe([this](const Response<APIPlaylistCatListData> &reply) {
              std::visit([=](const auto &value) {
                if constexpr (std::is_convertible_v<decltype(value), APIPlaylistCatListData>) {
//                    _songsModel->setRecommendationSongListsData(value);
                } else {
                    // errors
                }
              }, reply);
            });
        }
      private:
        std::variant<LoadingState,ReadyState> _state;
    };
} // namespace MusicPlayer::ViewModels

Q_DECLARE_METATYPE(MusicPlayer::ViewModels::LoadingState)
Q_DECLARE_METATYPE(MusicPlayer::ViewModels::ReadyStateItem)
Q_DECLARE_METATYPE(MusicPlayer::ViewModels::ReadyState)
