//
// Created by HUANG WEN JUN on 2019/12/9.
//
#include <QtAV>
#include <QtCore>
#include <memory>

namespace MusicPlayer::Player {
    class Player : public QObject {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(Player)
        Player();

      public:
        static void initInstance();

        static void freeInstance();

        static Player* instance();

      private:
        QtAV::VideoOutput *_output;
        QtAV::AVPlayer *_avPlayer;
        static Player* _instance;
    };
} // namespace MusicPlayer::Player
