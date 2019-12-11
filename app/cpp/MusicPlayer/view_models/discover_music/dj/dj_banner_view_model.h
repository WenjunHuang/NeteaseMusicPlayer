//
// Created by HUANG WEN JUN on 2019/12/7.
//

#pragma once

#include <QtCore>
#include <optional>
#include <folly/futures/Future.h>
#include "../../states.h"
#include "../../view_models.h"
#include "../../base_state_view_model.h"

namespace MusicPlayer::ViewModels {
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
      private:
        std::optional<folly::Future<std::nullopt_t>> _loading;
    };
}

Q_DECLARE_METATYPE(MusicPlayer::ViewModels::DJBannerViewModelReadyStateData)
Q_DECLARE_METATYPE(MusicPlayer::ViewModels::DJBannerViewModelReadyStateDataItem)
