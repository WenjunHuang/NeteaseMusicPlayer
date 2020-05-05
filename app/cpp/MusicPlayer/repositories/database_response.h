//
// Created by rick on 2020/5/5.
//

#pragma once
#include <variant>
#include <optional>
#include <QtCore/QtCore>
#include "wobjectdefs.h"
#include "wobjectimpl.h"
#include "tables.h"

namespace MusicPlayer::Repository {
    using DatabaseError = QString;

    template <typename T> using DatabaseResponse = std::variant<DatabaseError, T>;

    template <typename T> class DatabaseResponseHandler : public QObject {
        W_OBJECT(DatabaseResponseHandler)
      public:
        explicit DatabaseResponseHandler(QObject* parent = nullptr) : QObject{parent} {}

      signals:
        void finished(DatabaseResponse<T> const &response) W_SIGNAL(finished, response)
    };
}

W_REGISTER_ARGTYPE(MusicPlayer::Repository::DatabaseResponse<int>)
W_REGISTER_ARGTYPE(MusicPlayer::Repository::DatabaseResponse<std::optional<MusicPlayer::Repository::TImageCache>>)
W_REGISTER_ARGTYPE(MusicPlayer::Repository::DatabaseResponse<QVector<MusicPlayer::Repository::TImageCache>>)
W_REGISTER_ARGTYPE(MusicPlayer::Repository::DatabaseResponse<QVector<MusicPlayer::Repository::TPlayListSong>>)
W_OBJECT_IMPL_INLINE(MusicPlayer::Repository::DatabaseResponseHandler<T>,template<typename T>)
