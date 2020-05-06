//
// Created by HUANG WEN JUN on 2019/12/1.
//

#pragma once
#include <QtCore>
#include <variant>

namespace MusicPlayer::ViewModel {

    class StateKinds : public QObject {
        Q_OBJECT
      public:
        enum class Kind { UnInit, Loading, Ready, Error };
        Q_ENUM(Kind)

        static void registerMetaTypes();
    };

    struct UnInitState {
        Q_GADGET
        Q_PROPERTY(MusicPlayer::ViewModel::StateKinds::Kind kind READ kind)
      public:
        StateKinds::Kind kind() const { return StateKinds::Kind::UnInit; }

        inline bool operator==(const UnInitState& other) const { return true; }

        inline bool operator!=(const UnInitState& other) const { return false; }
    };

    struct LoadingState {
        Q_GADGET
        Q_PROPERTY(MusicPlayer::ViewModel::StateKinds::Kind kind READ kind)
      public:
        StateKinds::Kind kind() const { return StateKinds::Kind::Loading; }

        bool operator==(const LoadingState& other) const;

        bool operator!=(const LoadingState& other) const;
    };

    struct ErrorState {
        Q_GADGET
        Q_PROPERTY(MusicPlayer::ViewModel::StateKinds::Kind kind READ kind)
        Q_PROPERTY(QString message MEMBER message)
      public:
        QString message;
        StateKinds::Kind kind() const { return StateKinds::Kind::Error; }

        bool operator==(const ErrorState& other) const;
        bool operator!=(const ErrorState& other) const;
    };

    struct ReadyState {
        Q_GADGET
        Q_PROPERTY(MusicPlayer::ViewModel::StateKinds::Kind kind READ kind)
        Q_PROPERTY(QVariant data MEMBER data)
      public:
        QVariant data;
        StateKinds::Kind kind() const { return StateKinds::Kind::Ready; }

        bool operator==(const ReadyState& other) const;

        bool operator!=(const ReadyState& other) const;
    };

    using ViewModelState = std::variant<UnInitState, LoadingState, ErrorState, ReadyState>;

} // namespace MusicPlayer::ViewModels

Q_DECLARE_METATYPE(MusicPlayer::ViewModel::UnInitState)
Q_DECLARE_METATYPE(MusicPlayer::ViewModel::LoadingState)
Q_DECLARE_METATYPE(MusicPlayer::ViewModel::ErrorState)
Q_DECLARE_METATYPE(MusicPlayer::ViewModel::ReadyState)