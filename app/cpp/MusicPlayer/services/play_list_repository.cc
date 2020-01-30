//
// Created by rick on 2019/12/15.
//

#include "play_list_repository.h"
#include "repositories.h"
#include "util.h"
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>

namespace MusicPlayer::Service {
    using namespace boost::adaptors;
    using namespace MusicPlayer::Repository;
    using namespace MusicPlayer::Util;

    PlayListRepository* PlayListRepository::_instance = nullptr;

    int PlayListRepository::rowCount(const QModelIndex& parent) const { return _songs.size(); }

    QHash<int, QByteArray> PlayListRepository::roleNames() const {
        QHash<int, QByteArray> names;
        names[Roles::SongIdRole]       = "songId";
        names[Roles::ArtistsNamesRole] = "artists";
        names[Roles::ArtistsIdsRole]   = "artistsIds";
        names[Roles::SongNameRole]     = "songName";
        names[Roles::HasSQRole]        = "hasSQ";
        names[Roles::AlbumNameRole]    = "albumName";
        names[Roles::MusicVideoIdRole] = "musicVideoId";
        names[Roles::SongDurationRole] = "songDuration";
        names[Roles::IsPlayingRole]    = "isPlaying";
        names[Roles::IsPausedRole]     = "isPaused";
        return names;
    }

    QVariant PlayListRepository::data(const QModelIndex& index, int role) const {
        if (index.row() >= _songs.size())
            return QVariant();

        const auto& song = _songs.at(index.row());
        if (role == Roles::SongIdRole) {
            return song.id;
        }
        if (role == Roles::AlbumNameRole) {
            return song.album.albumName;
        }
        if (role == Roles::ArtistsNamesRole) {
            QVector<QString> artistNames;
            std::transform(song.artists.cbegin(), song.artists.cend(), std::back_inserter(artistNames), [](const auto& artist) {
                return artist.artistName;
            });
            return QVariant::fromValue(artistNames);
        }
        if (role == Roles::ArtistsIdsRole) {
            QVector<ArtistId> artistIds;
            std::transform(song.artists.cbegin(), song.artists.cend(), std::back_inserter(artistIds), [](const auto& artist) {
                return artist.artistId;
            });
            return QVariant::fromValue(artistIds);
        }
        if (role == Roles::HasSQRole) {
            return song.qualities.contains(SongQuality::Q990000);
        }
        if (role == Roles::MusicVideoIdRole) {
            return song.musicVideoId ? song.musicVideoId.value() : QVariant();
        }
        if (role == Roles::SongDurationRole)
            return song.duration;

        return QVariant();
    }

    void PlayListRepository::addSong(const PlayListSong& song) {
        if (contains(song.id))
            return;

        beginInsertRows(QModelIndex(), _songs.size(), _songs.size());
        _songs.append(song);
        syncToDb();
        endInsertRows();
    }

    void PlayListRepository::addSongs(const QVector<PlayListSong>& songs) {
        QVector<PlayListSong> toAdd;
        std::copy_if(
            songs.cbegin(), songs.cend(), std::back_inserter(toAdd), [this](const auto& song) { return !contains(song.id); });

        if (!toAdd.empty()) {
            beginInsertRows(QModelIndex(), _songs.size(), _songs.size() + toAdd.size() - 1);
            _songs.append(toAdd);
            syncToDb();
            endInsertRows();
        }
    }
    void PlayListRepository::removeSongById(SongId songId) {
        auto row = rowOfSong(songId);
        if (row) {
            beginRemoveRows(QModelIndex(), row.value(), row.value());
            _songs.remove(row.value());
            syncToDb();
            endRemoveRows();
        }
    }

    void PlayListRepository::clear() {
        if (!_songs.empty()) {
            beginRemoveRows(QModelIndex(), 0, _songs.size() - 1);
            _songs.clear();
            syncToDb();
            endRemoveRows();
        }
    }

    std::optional<SongId> PlayListRepository::nextSongOf(SongId songId) {
        if (auto row = rowOfSong(songId); row && row.value() >= 0 && row.value() < _songs.size() - 1) {
            return row.value() + 1;
        }

        return std::nullopt;
    }

    std::optional<SongId> PlayListRepository::prevSongOf(SongId songId) {
        if (auto row = rowOfSong(songId); row && row.value() > 0) {
            return row.value() - 1;
        }

        return std::nullopt;
    }

    bool PlayListRepository::contains(SongId songId) {
        return std::any_of(_songs.cbegin(), _songs.cend(), [songId](const auto& song) { return song.id == songId; });
    }

    void PlayListRepository::moveSongsToRow(int sourceFirst, int sourceLast, int destination) {
        beginMoveRows(QModelIndex(), sourceFirst, sourceLast, QModelIndex(), destination);
        std::rotate(_songs.begin() + sourceFirst, _songs.begin() + sourceLast, _songs.begin() + destination);
        syncToDb();
        endMoveRows();
    }

    std::optional<int> PlayListRepository::rowOfSong(SongId songId) {
        auto result = std::find_if(_songs.cbegin(), _songs.cend(), [songId](const auto& song) { return song.id == songId; });
        if (result == _songs.cend())
            return std::nullopt;
        else
            return result - _songs.cbegin();
    }

    void PlayListRepository::syncToDb() {
        auto dbInstance = DatabaseRepository::instance();
        std::vector<TPlayListSong> dbSongs;
        std::transform(_songs.cbegin(), _songs.cend(), std::back_inserter(dbSongs), [](const PlayListSong& song) {
            QStringList qualities;
            std::transform(
                song.qualities.cbegin(), song.qualities.cend(), std::back_inserter(qualities), [](const SongQuality& q) {
                    auto name = magic_enum::enum_name(q);
                    return QString(name.data());
                });

            QStringList artists;
            std::transform(song.artists.cbegin(), song.artists.cend(), std::back_inserter(artists), [](const auto& artist) {
                return QString("%1:%2").arg(artist.artistId).arg(artist.artistName);
            });

            return TPlayListSong{
                -1,
                song.id,
                song.name.toUtf8().toStdString(),
                song.coverImgUrl.toUtf8().toStdString(),
                song.duration,
                qualities.join(',').toUtf8().toStdString(),
                artists.join(',').toUtf8().toStdString(),
                song.album.albumId,
                song.album.albumName.toUtf8().toStdString(),
                song.musicVideoId.has_value() ? std::make_unique<MusicVideoId>(song.musicVideoId.value()) : nullptr,
            };
        });
        dbInstance->replacePlayListSongs(std::move(dbSongs)).get();
    }

    void PlayListRepository::loadFromDb() {
        auto dbInstance = DatabaseRepository::instance();
        auto records    = dbInstance->getAllPlayListSongs().get();

        _songs.clear();

        std::transform(records.cbegin(), records.cend(), std::back_inserter(_songs), [](const TPlayListSong& record) {
            auto artistsList = QString(record.artists.data()).split(',');
            QVector<PlayListSongArtist> artists;
            std::transform(artistsList.cbegin(), artistsList.cend(), std::back_inserter(artists), [](const auto& artist) {
                QRegExp reg{"(\\d+):(\\w+)"};
                auto split = artist.split(':');
                return PlayListSongArtist{split[0].toInt(), split[1]};
            });

            QVector<SongQuality> qualities;
            auto qualitiesList = QString(record.qualities.data()).split(',');
            boost::copy(qualitiesList |
                            transformed([](const auto& v) { return magic_enum::enum_cast<SongQuality>(v.toStdString()); }) |
                            filtered([](const auto& v) { return v.has_value(); }) |
                            transformed([](const auto& v) { return v.value(); }),
                        std::back_inserter(qualities));

            return PlayListSong{
                record.id,
                QString(record.name.data()),
                QString(record.coverImgUrl.data()),
                PlayListSongAlbum{record.albumId, QString(record.albumName.data())},
                record.duration,
                qualities,
                artists,
                record.musicVideoId ? std::optional(*record.musicVideoId) : std::nullopt,
            };
        });
    }

    void PlayListRepository::initInstance() {
        if (_instance == nullptr)
            _instance = new PlayListRepository();
    }

    void PlayListRepository::freeInstance() {
        if (_instance != nullptr) {
            delete _instance;
            _instance = nullptr;
        }
    }

    PlayListRepository* PlayListRepository::instance() { return _instance; }
    PlayListRepository::PlayListRepository() {}

} // namespace MusicPlayer::Service
