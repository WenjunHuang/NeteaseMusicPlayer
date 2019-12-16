//
// Created by rick on 2019/12/15.
//

#pragma once
#include "../commons.h"
#include <QtCore>
#include <algorithm>
#include <optional>

namespace MusicPlayer::Repository {
    struct PlayListSongArtist {
        ArtistId artistId;
        QString artistName;
    };

    struct PlayListSongAlbum {
        AlbumId albumId;
        QString albumName;
    };

    struct PlayListSong {
        SongId id;
        QString name;
        QString coverImgUrl;
        int duration;
        QString qualities;
        QString artistsNames;
    };

    class PlayListRepository : public QAbstractListModel {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(PlayListRepository)
        PlayListRepository();

      public:
        enum Roles : int {
            SongIdRole = Qt::UserRole + 1,
            SongNameRole,
            ArtistsIdsRole,
            ArtistsNamesRole,
            HasSQRole,
            AlbumNameRole,
            MusicVideoIdRole,
            SongDurationRole
        };

        int rowCount(const QModelIndex& parent) const override;

        QHash<int, QByteArray> roleNames() const override;

        QVariant data(const QModelIndex& index, int role) const override;

        QVector<PlayListSong> allSongsInPlayList() { return _songs; }

        void addSong(const PlayListSong& song);

        void addSongs(const QVector<PlayListSong>& songs);

        void removeSongById(SongId songId);

        void clear();

        std::optional<SongId> nextSongOf(SongId songId);

        bool hasNext(SongId songId) { return nextSongOf(songId) != std::nullopt; }

        std::optional<SongId> prevSongOf(SongId songId);
        bool hasPrevious(SongId songId) { return prevSongOf(songId) != std::nullopt; }

        bool contains(SongId songId);

        void moveSongsToRow(int sourceFirst, int sourceLast, int destination);

        std::optional<int> rowOfSong(SongId songId);

      private:
        QVector<TPlayListSong> _songs;
    };
} // namespace MusicPlayer::Repository
