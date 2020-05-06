//
// Created by HUANG WEN JUN on 2019/12/7.
//

#pragma once

#include "../../base_state_view_model.h"
#include "../../states.h"
#include "../../view_model.h"
#include <QtCore>
#include <optional>

namespace MusicPlayer::ViewModel {
    struct DJBannerViewModelReadyStateDataItem {
        Q_GADGET
        Q_PROPERTY(QString imageUrl MEMBER imageUrl)
        Q_PROPERTY(QString typeTitle MEMBER typeTitle)

      public:
        QString imageUrl;
        QString typeTitle;
    };

    struct DJBannerViewModelReadyStateData {
        Q_GADGET
        Q_PROPERTY(QVariantList bannerItems MEMBER bannerItems)
      public:
        QVariantList bannerItems; // DJBannerViewModelReadyStateDataItem
    };

    class DJBannerViewModel: public BaseStateViewModel {
        Q_OBJECT
      public:
        explicit DJBannerViewModel(QObject* parent = nullptr):BaseStateViewModel{parent} {}

        Q_INVOKABLE void reload();

        static void registerMetaTypes();
    };
}

Q_DECLARE_METATYPE(MusicPlayer::ViewModel::DJBannerViewModelReadyStateData)
Q_DECLARE_METATYPE(MusicPlayer::ViewModel::DJBannerViewModelReadyStateDataItem)
