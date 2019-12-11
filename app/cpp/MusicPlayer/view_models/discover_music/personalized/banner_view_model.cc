//
// Created by rick on 2019/11/9.
//

#include "banner_view_model.h"
#include "../../../util/executor.h"

namespace MusicPlayer::ViewModels {
    using namespace MusicPlayer::Util;

    BannerViewModel::BannerViewModel(QObject* parent) : BaseStateViewModel(parent) {}

    void BannerViewModel::reload() {
        if (_loading && !_loading->isReady())
            return; // 还在加载中

        MusicAPI api;
        _loading = api.banner()
                       .via(AppExecutor::instance()->getMainExecutor().get())
                       .thenValue([this](Response<APIBannersData>&& reply) {
                           std::visit(
                               [=](const auto& value) {
                                   if constexpr (std::is_convertible_v<decltype(value), APIBannersData>) {
                                       QVariantList items;
                                       for (const auto& banner : value.banners) {
                                           items.append(QVariant::fromValue(
                                               BannerViewModelReadyDataItem{banner.imageUrl, banner.typeTitle}));
                                       }

                                       setState(ReadyState{QVariant::fromValue(BannerViewModelReadyData{items})});
                                   } else {
                                       // errors
                                   }
                               },
                               reply);
                           return std::nullopt;
                       });
    }

    void BannerViewModel::registerMetaTypes() {
        qRegisterMetaType<BannerViewModelReadyDataItem>();
        qRegisterMetaType<BannerViewModelReadyData>();
    }

} // namespace MusicPlayer::ViewModels
