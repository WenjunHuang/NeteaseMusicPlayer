//
// Created by HUANG WEN JUN on 2019/12/9.
//
#include "../commons.h"
#include <QtAV/QtAV>
//#include <QtAV>
#include <QtCore>
#include <folly/futures/Future.h>
#include <memory>
#include <optional>

namespace MusicPlayer::Player {

    struct CurrentSong {
        SongId songId;
        SongQuality songQuality;
        qint64 position;
    };

    struct EmptyState {};

    struct LoadingAudioState {
        SongId songId;
        SongQuality songQuality;
        qint64 position;
        folly::Future<folly::Unit> future;

        void cancel() {
            if (future.valid() && !future.isReady())
                future.cancel();
        }
    };

    struct PlayingAudioState {
        SongId songId;
        SongQuality songQuality;
        qint64 position;
    };

    struct PausedAudioState {
        SongId songId;
        SongQuality songQuality;
        qint64 position;
    };

    struct ErrorState {
        std::optional<SongId> latestSongId;
        std::optional<SongQuality> latestSongQuality;
        std::optional<qint64> latestPosition;

        QString errorMessage;
    };

    using PlayerState = std::variant<EmptyState, PlayingAudioState, PausedAudioState, LoadingAudioState, ErrorState>;

    class AudioPlayer : public QObject {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(AudioPlayer)
        //        Q_PROPERTY(SongId currentSongId READ currentSongId NOTIFY currentSongIdChanged)
        //        Q_PROPERTY(MusicPlayer::AudioPlayer::SongPlayingState READ currentSongPlayingState NOTIFY
        //        currentSongPlayingStateChanged)

        AudioPlayer();

      public:
        enum class SongPlayingState { Playing, Paused };
        Q_ENUM(SongPlayingState)

      signals:
        void stopped(SongId songId);
        void loading(SongId songId);
        void playing(SongId songId);
        void paused(SongId songId);

      public:
        static void initInstance();

        static void freeInstance();

        static AudioPlayer* instance();

        void playAudio(SongId songId, SongQuality quality);
        void pauseAudio();
        void resumeAudio();

        std::optional<CurrentSong> getCurrentSong();

      private:
        void setState(PlayerState&& state);
        void fetchSongUrlAndPlay(SongId songId, SongQuality songQuality, qint64 position);
        void positionChanged(qint64 position);

      private:
        QtAV::VideoOutput* _output = nullptr;
        QtAV::AVPlayer* _avPlayer;
        int _avPlayerNotifyInterval = 1000;

        PlayerState _state;

        static AudioPlayer* _instance;
    };
} // namespace MusicPlayer::AudioPlayer
