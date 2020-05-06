//
// Created by rick on 2019/11/9.
//

#pragma once

#include "../../base_state_view_model.h"
#include "api.h"
#include <QtQml/QQmlParserStatus>
#include <QtCore/QtCore>

namespace MusicPlayer::ViewModel {
    using namespace MusicPlayer::API;

    struct BannerViewModelReadyDataItem {
        Q_GADGET
        Q_PROPERTY(QString imageUrl MEMBER imageUrl)
        Q_PROPERTY(QString typeTitle MEMBER typeTitle)
      public:
        QString imageUrl;
        QString typeTitle;
    };

    struct BannerViewModelReadyData {
        Q_GADGET
        Q_PROPERTY(QVariantList bannerItems MEMBER bannerItems)
      public:
        QVariantList bannerItems;
    };

    class BannerViewModel : public BaseStateViewModel,public QQmlParserStatus {
        Q_OBJECT
        Q_INTERFACES(QQmlParserStatus)

      public:
        BannerViewModel(QObject* parent = nullptr);
        void componentComplete() override;
        void classBegin() override {}

        static void registerMetaTypes();
      private:
        void loadBannerData();

    };
} // namespace MusicPlayer::ViewModels

Q_DECLARE_METATYPE(MusicPlayer::ViewModel::BannerViewModelReadyDataItem)
Q_DECLARE_METATYPE(MusicPlayer::ViewModel::BannerViewModelReadyData)
