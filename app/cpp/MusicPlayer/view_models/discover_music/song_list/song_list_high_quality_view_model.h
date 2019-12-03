//
// Created by HUANG WEN JUN on 2019/12/1.
//

#pragma once
#include "../../states.h"
#include <QtCore>
#include <folly/futures/Future.h>
#include <optional>

namespace MusicPlayer::ViewModels {
    struct SongListHighQualityReadyData {
        Q_GADGET
        Q_PROPERTY(QString name MEMBER name)
        Q_PROPERTY(QString copywriter MEMBER copywriter)
        Q_PROPERTY(QUrl coverImgUrl MEMBER coverImgUrl)
      public:
        QString name;
        QString copywriter;
        QUrl coverImgUrl;
    };

    class SongListHighQualityViewModel: public QObject {
        Q_OBJECT
        Q_PROPERTY(QVariant state READ state NOTIFY stateChanged)
        Q_PROPERTY(QString categoryName READ categoryName WRITE setCategoryName)
      public:
        explicit SongListHighQualityViewModel(QObject *parent = nullptr):QObject(parent){}

        QVariant state() const {
            return QVariant::fromStdVariant(_state);
        }

        QString categoryName() const {
            return _categoryName;
        }

        void setCategoryName(const QString& catName) {
            if (_categoryName == catName)
                return;

            _categoryName = catName;
            reload();
        }

        static void registerMetaTypes();

      signals:
        void stateChanged();

      private:
        QString _categoryName;
        ViewModelState _state;
        std::optional<folly::Future<std::nullopt_t>> _loading;

        void reload();

        void setState(ViewModelState state);
    };
}

Q_DECLARE_METATYPE(MusicPlayer::ViewModels::SongListHighQualityReadyData)