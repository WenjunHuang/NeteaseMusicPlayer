//
// Created by rick on 2019/12/15.
//

#include "play_list_repository.h"

namespace MusicPlayer::Service {
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
    }
    void PlayListRepository::addSong(const PlayListSong& song) {
        if (contains(song.id))
            return;

        beginInsertRows(QModelIndex(), _songs.size(), _songs.size());
        _songs.append(song);
        endInsertRows();
    }
    void PlayListRepository::addSongs(const QVector<PlayListSong>& songs) {
        QVector<PlayListSong> toAdd;
        std::copy_if(songs.cbegin(), songs.cend(), std::back_inserter(toAdd), [this](const auto& song) {
            return !contains(song.id);
        });

        if (!toAdd.empty()) {
            beginInsertRows(QModelIndex(), _songs.size(), _songs.size() + toAdd.size() - 1);
            _songs.append(toAdd);
            endInsertRows();
        }
    }
    void PlayListRepository::removeSongById(SongId songId) {
        auto row = rowOfSong(songId);
        if (row) {
            beginRemoveRows(QModelIndex(), row.value(), row.value());
            _songs.remove(row.value());
            endRemoveRows();
        }
    }

    void PlayListRepository::clear() {
        if (!_songs.empty()) {
            beginRemoveRows(QModelIndex(), 0, _songs.size() - 1);
            _songs.clear();
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
        endMoveRows();
    }

    std::optional<int> PlayListRepository::rowOfSong(SongId songId) {
        auto result =
            std::find_if(_songs.cbegin(), _songs.cend(), [songId](const auto& song) { return song.id == songId; });
        if (result == _songs.cend())
            return std::nullopt;
        else
            return result - _songs.cbegin();
    }
} // namespace MusicPlayer::Repository
