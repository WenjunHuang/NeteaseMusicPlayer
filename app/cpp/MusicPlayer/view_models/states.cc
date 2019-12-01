//
// Created by HUANG WEN JUN on 2019/12/1.
//
#include "states.h"

namespace MusicPlayer::ViewModels {

    bool LoadingState::operator==(const MusicPlayer::ViewModels::LoadingState& other) const { return true; }

    bool LoadingState::operator!=(const LoadingState& other) const { return false; }

    bool ErrorState::operator==(const ErrorState& other) const { return message == other.message; }

    bool ErrorState::operator!=(const ErrorState& other) const { return !operator==(other); }

    bool ReadyState::operator==(const ReadyState& other) const {return data == other.data;}

    bool ReadyState::operator!=(const ReadyState& other) const { return !operator==(other); }

    void StateKinds::registerMetaTypes() {
        qRegisterMetaType<UnInitState>();
        qRegisterMetaType<LoadingState>();
        qRegisterMetaType<ReadyState>();
        qRegisterMetaType<ErrorState>();
    }
}