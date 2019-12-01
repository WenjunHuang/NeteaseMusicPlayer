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

    class StateKinds: public QObject {
        Q_OBJECT
      public:
        enum class Kind { UnInit, Loading, Ready, Error };
        Q_ENUM(Kind)
    };

    struct UnInitState {
        Q_GADGET
        Q_PROPERTY(MusicPlayer::ViewModels::StateKinds::Kind kind READ kind)
      public:
        StateKinds::Kind kind() const { return StateKinds::Kind::UnInit; }

        inline bool operator==(const UnInitState& other) const {
            return true;
        }

        inline bool operator!=(const UnInitState& other) const {
            return false;
        }
    };

    struct LoadingState {
        Q_GADGET
        Q_PROPERTY(MusicPlayer::ViewModels::StateKinds::Kind kind READ kind)
      public:
        StateKinds::Kind kind() const { return StateKinds::Kind::Loading; }

        bool operator==(const LoadingState& other) const;

        bool operator!=(const LoadingState& other) const;
    };

    struct ErrorState {
        Q_GADGET
        Q_PROPERTY(MusicPlayer::ViewModels::StateKinds::Kind kind READ kind)
        Q_PROPERTY(QString message MEMBER message)
      public:
        QString message;
        StateKinds::Kind kind() const { return StateKinds::Kind::Error; }

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
        Q_PROPERTY(MusicPlayer::ViewModels::StateKinds::Kind kind READ kind)
        Q_PROPERTY(QString allName MEMBER allName)
        Q_PROPERTY(QVariantList items MEMBER items)
      public:
        QString allName;
        QVariantList items;
        StateKinds::Kind kind() const { return StateKinds::Kind::Ready; }

        bool operator==(const ReadyState& other) const;

        bool operator!=(const ReadyState& other) const;
    };

    using State = std::variant<UnInitState, LoadingState, ErrorState, ReadyState>;

    class SongCategoryListViewModel : public QObject, public QQmlParserStatus {
        Q_OBJECT
        Q_INTERFACES(QQmlParserStatus)
        Q_PROPERTY(QVariant state READ state NOTIFY stateChanged)
      public:
        explicit SongCategoryListViewModel(QObject* parent = nullptr) : QObject(parent) {}

        QVariant state() const { return QVariant::fromStdVariant(_state); }

        void classBegin() override {}

        void componentComplete() override;

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
