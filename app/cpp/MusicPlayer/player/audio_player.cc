#include "audio_player.h"
#include "api.h"
#include "util.h"

namespace MusicPlayer::Player {
    using namespace MusicPlayer::API;
    using namespace MusicPlayer::Util;
    using namespace QtAV;
    AudioPlayer* AudioPlayer::_instance = nullptr;

    AudioPlayer::AudioPlayer() {
        _avPlayer = new AVPlayer(this);
        connect(_avPlayer, &AVPlayer::stopped, [this]() {
            std::visit(overload{[this](const PlayingAudioState& playingState) { emit stopped(playingState.songId); },
                                [this](const PausedAudioState& pausedState) { emit stopped(pausedState.songId); },
                                [](const auto& other) {}},
                       _state);
        });

        connect(_avPlayer, &AVPlayer::notifyIntervalChanged, [=]() { _avPlayerNotifyInterval = _avPlayer->notifyInterval(); });
        connect(_avPlayer, &AVPlayer::positionChanged, [=](qint64 position) {
            std::visit(overload{[=](const PlayingAudioState& state) {
                                    setState(PlayingAudioState{
                                        state.songId,
                                        state.songQuality,
                                        position,
                                    });
                                },
                                [](const PausedAudioState& state) {

                                },
                                [](const auto& state) {}},
                       _state);
        });
    }

    void AudioPlayer::initInstance() {
        if (_instance == nullptr) {
            _instance = new AudioPlayer;
        }
    }

    AudioPlayer* AudioPlayer::instance() { return _instance; }

    void AudioPlayer::freeInstance() {
        if (_instance) {
            delete _instance;
            _instance = nullptr;
        }
    }

    void AudioPlayer::playAudio(SongId songId, SongQuality quality) {
        std::visit(overload{[=](const PlayingAudioState& state) {
                                if (songId == state.songId && quality == state.songQuality)
                                    return;
                                else {
                                    fetchSongUrlAndPlay(songId, quality, songId == state.songId ? state.position : 0);
                                }
                            },
                            [=](const PausedAudioState& state) {
                                if (songId == state.songId && quality == state.songQuality) {
                                    _avPlayer->play();
                                    setState(PlayingAudioState{
                                        songId,
                                        quality,
                                        state.position,
                                    });
                                } else {
                                    fetchSongUrlAndPlay(songId, quality, songId == state.songId ? state.position : 0);
                                }
                            },
                            [=](LoadingAudioState& state) {
                                if (songId == state.songId && quality == state.songQuality) {
                                    return;
                                } else {
                                    fetchSongUrlAndPlay(songId, quality, 0);
                                }
                            },
                            [=](EmptyState& state) { fetchSongUrlAndPlay(songId, quality, 0); },
                            [](const auto& other) {

                            }},
                   _state);
    }

    void AudioPlayer::fetchSongUrlAndPlay(SongId songId, SongQuality quality, qint64 position) {
        auto api = MusicAPI::instance();
        auto response = api->songUrl(songId, quality);
        connect(response, &APIResponseHandler<APISongUrlData>::finished, [=](APIResponse<APISongUrlData> response) {
            std::visit(overload{[=](const APISongUrlData& urlData) {
                                    qDebug() << urlData.data[0].url;
                                    _avPlayer->setFile(urlData.data[0].url);
                                    _avPlayer->load();
                                    _avPlayer->setPosition(position);

                                    setState(PlayingAudioState{
                                        songId,
                                        quality,
                                        position,
                                    });
                                    _avPlayer->play();
                                    qDebug() << "ok";
                                },
                                [](const auto& error) { qDebug() << "Error"; }},
                       response);
        });
        setState(LoadingAudioState{
            songId,
            quality,
            position
        });
    }

    void AudioPlayer::pauseAudio() {
        std::visit(overload{[=](const PlayingAudioState& state) {
                                _avPlayer->pause();
                                setState(PausedAudioState{
                                    state.songId,
                                    state.songQuality,
                                    state.position,
                                });
                            },
                            [](const auto& state) {}},
                   _state);
    }

    void AudioPlayer::resumeAudio() {
        auto newState = std::visit(overload{[=](PausedAudioState&& state) {
                                                _avPlayer->play();
                                                return PlayerState{PlayingAudioState{
                                                    state.songId,
                                                    state.songQuality,
                                                    state.position,
                                                }};
                                            },
                                            [](auto&& state) { return PlayerState{std::move(state)}; }},
                                   std::move(_state));
        setState(std::move(newState));
    }

    std::optional<CurrentSong> AudioPlayer::getCurrentSong() {
        return std::visit(overload{[](const PlayingAudioState& state) {
                                       return std::make_optional(CurrentSong{
                                           state.songId,
                                           state.songQuality,
                                           state.position,
                                       });
                                   },
                                   [](const PausedAudioState& state) {
                                       return std::make_optional(CurrentSong{
                                           state.songId,
                                           state.songQuality,
                                           state.position,
                                       });
                                   },
                                   [](const LoadingAudioState& state) {
                                       return std::make_optional(CurrentSong{
                                           state.songId,
                                           state.songQuality,
                                           state.position,
                                       });
                                   },
                                   [](const auto& state) { return std::optional<CurrentSong>(); }

                          },
                          _state);
    }

    void AudioPlayer::setState(PlayerState&& state) {
        _state = std::move(state);
        std::visit(overload{[=](const PlayingAudioState& state) {
                                qDebug() << "Playing:" << state.songId << ",position:" << state.position
                                         << ",seconds: " << state.position / _avPlayerNotifyInterval;
                            },
                            [](const auto& state) {}},
                   _state);
    }

    void AudioPlayer::positionChanged(qint64 position) {
        std::visit(overload{[=](const PlayingAudioState& state) {
                                setState(PlayingAudioState{
                                    state.songId,
                                    state.songQuality,
                                    position,
                                });
                            },
                            [=](const PausedAudioState& state) {
                                setState(PausedAudioState{
                                    state.songId,
                                    state.songQuality,
                                    position,
                                });
                            },
                            [](const auto& state) {}},
                   _state);
    }
} // namespace MusicPlayer::Player