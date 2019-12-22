#include "player.h"
#include "../api/api.h"
#include "../util/util.h"

namespace MusicPlayer::Player {
    using namespace MusicPlayer::API;
    using namespace MusicPlayer::Util;
    using namespace QtAV;
    Player* Player::_instance = nullptr;

    Player::Player() {
        _avPlayer = new AVPlayer(this);
        connect(_avPlayer, &AVPlayer::stopped, [this]() {
            std::visit(overload{[this](const PlayingAudioState& playingState) { emit stopped(playingState.songId); },
                                [this](const PausedAudioState& pausedState) { emit stopped(pausedState.songId); },
                                [](const auto& other) {}},
                       _state);
        });

        connect(_avPlayer,&AVPlayer::notifyIntervalChanged,[=](){ _avPlayerNotifyInterval = _avPlayer->notifyInterval(); });
        connect(_avPlayer,&AVPlayer::positionChanged,[=](qint64 position) {

        });
    }

    void Player::initInstance() {
        if (_instance == nullptr) {
            _instance = new Player;
        }
    }

    Player* Player::instance() { return _instance; }

    void Player::freeInstance() {
        if (_instance) {
            delete _instance;
            _instance = nullptr;
        }
    }

    void Player::playAudio(SongId songId, SongQuality quality) {
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
                                    state.cancel();
                                    fetchSongUrlAndPlay(songId, quality, 0);
                                }
                            },
                            [](const auto& other) {

                            }},
                   _state);
    }

    void Player::fetchSongUrlAndPlay(SongId songId, SongQuality quality, qint64 position) {
        MusicAPI api;
        auto f = api.songUrl(songId, static_cast<int>(quality)).via(mainExecutor()).thenValue([=](Response<QString> response) {
            std::visit(overload{[=](const QString& url) {
                                    this->_avPlayer->setFile(url);
                                    this->_avPlayer->load();
                                    this->_avPlayer->setPosition(position);

                                    this->setState(PlayingAudioState{
                                        songId,
                                        quality,
                                        position,
                                    });
                                    this->_avPlayer->play();
                                },
                                [](const auto& error) {

                                }},
                       response);
        });
        setState(LoadingAudioState{
            songId,
            quality,
            position,
            std::move(f),
        });
    }

    void Player::pauseAudio() {
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

    void Player::resumeAudio() {
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


    std::optional<CurrentSong> Player::getCurrentSong() {
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

    void Player::setState(PlayerState&& state) { _state = std::move(state); }
    void Player::positionChanged() {}
} // namespace MusicPlayer::Player