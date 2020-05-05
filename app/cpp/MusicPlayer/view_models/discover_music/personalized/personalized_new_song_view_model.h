//
// Created by rick on 2019/11/10.
//

#pragma once

#include "../../base_state_view_model.h"
#include "api.h"
#include <QtCore>
#include <QtQml/QQmlParserStatus>
#include <optional>

namespace MusicPlayer::ViewModels {
    using namespace MusicPlayer::API;

    class PersonalizedNewSongListModel : public QAbstractListModel {
    Q_OBJECT
    public:
        enum Roles {
            ImageUrl = Qt::UserRole + 1,
            Id,
            Name,
            NameAlias,
            IsSq,
            MvId,
            Artists,
            IsCurrentSong,
            IsCurrentSongPlaying
        };
        PersonalizedNewSongListModel(QObject *parent);

        QHash<int, QByteArray> roleNames() const override;

        int rowCount(const QModelIndex &index) const override;

        QVariant data(const QModelIndex &index, int role) const override;

        void setPersonalizedNewSongData(const APIPersonalizedNewSongData &data);

    private:
        QVector<APIPersonalizedNewSongResultData> _data;

    };

    class PersonalizedNewSongViewModel : public BaseStateViewModel,public QQmlParserStatus {
        Q_OBJECT
        Q_INTERFACES(QQmlParserStatus)
        Q_PROPERTY(QAbstractListModel* newSongListModel READ newSongListModel)
    public:
        explicit PersonalizedNewSongViewModel(QObject *parent = nullptr);


        QAbstractListModel* newSongListModel() const;

        void componentComplete() override {
          loadData();
        }

        void classBegin() override {}

    private:
        void loadData();

        PersonalizedNewSongListModel *_newSongModel;
    };
}



