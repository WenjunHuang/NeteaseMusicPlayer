//
// Created by rick on 2019/11/9.
//

#pragma once

#include <QtCore>
#include <folly/futures/Future.h>
#include "../../../api/api.h"
#include "../../../api/data/banner.h"
#include "../../base_state_view_model.h"

namespace MusicPlayer::ViewModels {
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

    class BannerViewModel : public BaseStateViewModel {
        Q_OBJECT
    public:
        BannerViewModel(QObject *parent = nullptr);

        Q_INVOKABLE void reload();

        static void registerMetaTypes();
    private:
        std::optional<folly::Future<std::nullopt_t>> _loading;
    };
}

Q_DECLARE_METATYPE(MusicPlayer::ViewModels::BannerViewModelReadyDataItem)
Q_DECLARE_METATYPE(MusicPlayer::ViewModels::BannerViewModelReadyData)


