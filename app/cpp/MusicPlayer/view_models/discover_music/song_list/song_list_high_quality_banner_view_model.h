//
// Created by HUANG WEN JUN on 2019/12/1.
//

#pragma once
#include <QtCore>
#include <optional>
#include "../../states.h"
#include "../../base_state_view_model.h"

namespace MusicPlayer::ViewModels {
    struct SongListHighQualityBannerReadyData {
        Q_GADGET
        Q_PROPERTY(QString name MEMBER name)
        Q_PROPERTY(QString copywriter MEMBER copywriter)
        Q_PROPERTY(QUrl coverImgUrl MEMBER coverImgUrl)
      public:
        QString name;
        QString copywriter;
        QUrl coverImgUrl;
    };

    class SongListHighQualityBannerViewModel : public BaseStateViewModel {
        Q_OBJECT
        Q_PROPERTY(QString categoryName READ categoryName WRITE setCategoryName)
      public:
        explicit SongListHighQualityBannerViewModel(QObject *parent = nullptr):BaseStateViewModel(parent){}

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

      private:
        QString _categoryName;

        void reload();
    };
}

Q_DECLARE_METATYPE(MusicPlayer::ViewModels::SongListHighQualityBannerReadyData)