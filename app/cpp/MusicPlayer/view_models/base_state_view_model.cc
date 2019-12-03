//
// Created by HUANG WEN JUN on 2019/12/3.
//

#include "base_state_view_model.h"
void MusicPlayer::ViewModels::BaseStateViewModel::setState(const MusicPlayer::ViewModels::ViewModelState& state) {
    if (state == _state)
        return;

    _state = state;
    emit stateChanged();
}
QVariant MusicPlayer::ViewModels::BaseStateViewModel::state() const { return QVariant::fromStdVariant(_state); }
