//
// Created by rick on 2019/11/13.
//

#pragma once
#include "../api/api.h"
#include "../repositories/repositories.h"
#include "../util/util.h"
#include <QtCore>
#include <QtQml/QQmlParserStatus>

namespace MusicPlayer::ViewModels {
    using namespace MusicPlayer::API;
    using namespace MusicPlayer::Repository;
    using namespace MusicPlayer::Util;

    enum class StateKind { UnInit, Loading, Ready, Error };

    struct UnInitState {
        Q_GADGET
      public:
        StateKind kind() const { return StateKind::UnInit; }

        inline bool operator==(const UnInitState& other) const {
            return true;
        }

        inline bool operator!=(const UnInitState& other) const {
            return false;
        }
    };

    struct LoadingState {
        Q_GADGET
        Q_PROPERTY(StateKind kind READ kind)
      public:
        StateKind kind() const { return StateKind::Loading; }

        bool operator==(const LoadingState& other) const;

        bool operator!=(const LoadingState& other) const;
    };

    struct ErrorState {
        Q_GADGET
        Q_PROPERTY(StateKind kind READ kind)
        Q_PROPERTY(QString message MEMBER message)
      public:
        QString message;
        StateKind kind() const { return StateKind::Error; }

        bool operator==(const ErrorState& other) const;
        bool operator!=(const ErrorState& other) const;
    };

    struct ReadyStateItem {
        Q_GADGET
        Q_PROPERTY(QString name MEMBER name)
        Q_PROPERTY(QString icon MEMBER icon)
        Q_PROPERTY(QVariantList subCats MEMBER subCats)
      public:
        QString name;
        QString icon;
        QVariantList subCats; // APIPlaylistCatListItemData

        bool operator==(const ReadyStateItem& other) const;

        bool operator!=(const ReadyStateItem& other) const;
    };

    struct ReadyState {
        Q_GADGET
        Q_PROPERTY(StateKind kind READ kind)
        Q_PROPERTY(QString allName MEMBER allName)
        Q_PROPERTY(QVariantList items MEMBER items)
      public:
        QString allName;
        QVariantList items;
        StateKind kind() const { return StateKind::Ready; }

        bool operator==(const ReadyState& other) const;

        bool operator!=(const ReadyState& other) const;
    };

    using State = std::variant<UnInitState, LoadingState, ErrorState, ReadyState>;

    class SongCategoryListViewModel : public QObject, public QQmlParserStatus {
        Q_OBJECT
        Q_INTERFACES(QQmlParserStatus)
        Q_ENUM(StateKind)
        Q_PROPERTY(QVariant state READ state NOTIFY stateChanged)
      public:
        explicit SongCategoryListViewModel(QObject* parent = nullptr) : QObject(parent) {}

        QVariant state() const { return QVariant::fromStdVariant(_state); }

        void classBegin() override {}

        void componentComplete() override { reload(); }

        Q_INVOKABLE void reload();
      signals:
        void stateChanged();

      private:
        void setState(const State& state);
        State _state;
    };
} // namespace MusicPlayer::ViewModels

Q_DECLARE_METATYPE(MusicPlayer::ViewModels::LoadingState)
Q_DECLARE_METATYPE(MusicPlayer::ViewModels::ErrorState)
Q_DECLARE_METATYPE(MusicPlayer::ViewModels::ReadyStateItem)
Q_DECLARE_METATYPE(MusicPlayer::ViewModels::ReadyState)
Q_DECLARE_METATYPE(MusicPlayer::ViewModels::UnInitState)
