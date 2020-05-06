//
// Created by HUANG WEN JUN on 2019/12/3.
//

#include "base_state_view_model.h"
#include <variant>
namespace MusicPlayer::ViewModel {
    void BaseStateViewModel::setState(const ViewModelState& state) {
        if (state == _state)
            return;

        _state = state;
        emit stateChanged();
    }
    QVariant BaseStateViewModel::state() const { return QVariant::fromStdVariant(_state); }
} // namespace MusicPlayer::ViewModel
