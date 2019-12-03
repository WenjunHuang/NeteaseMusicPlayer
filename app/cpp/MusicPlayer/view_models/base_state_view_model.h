//
// Created by HUANG WEN JUN on 2019/12/3.
//

#pragma once
#include <QtCore>
#include "states.h"

namespace MusicPlayer::ViewModels {
    class BaseStateViewModel : public QObject {
        Q_OBJECT
        Q_PROPERTY(QVariant state READ state NOTIFY stateChanged)
      public:
        BaseStateViewModel(QObject* parent = nullptr) : QObject(parent) {}

        QVariant state() const;

      signals:
        void stateChanged();

      protected:
        void setState(const ViewModelState& state);
        ViewModelState _state;
    };
} // namespace MusicPlayer::ViewModels
