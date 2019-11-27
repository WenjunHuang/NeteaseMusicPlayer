//
// Created by rick on 2019/11/10.
//

#pragma once
#include <QObject>
#include <QtCore/QString>

namespace MusicPlayer::Util {
    QString getUserIDString();

    class DeleteLater {
      public:
        DeleteLater(QObject* toDelete) : _toDelete { toDelete } {}

        ~DeleteLater() {
            if (_toDelete)
                _toDelete->deleteLater();
        }

      private:
        QObject* _toDelete;
    };
} // namespace MusicPlayer::Util
