//
// Created by rick on 2019/11/9.
//

#include "banner_view_model.h"
#include "util.h"
#include <variant>

namespace MusicPlayer::ViewModels {
    //    using namespace MusicPlayer::Util;

    BannerViewModel::BannerViewModel(QObject* parent) : BaseStateViewModel(parent) {}

    void BannerViewModel::loadBannerData() {
        if (auto ptr = std::get_if<LoadingState>(&_state)) {
            return;
        } else {
            MusicAPI api;
            auto result = api.banner();
            connect(result, &APIResponseHandler<APIBannersData>::finished, [this](const APIResponse<APIBannersData>& reply) {
                std::visit(
                    [=](const auto& value) {
                        if constexpr (std::is_convertible_v<decltype(value), APIBannersData>) {
                            QVariantList items;
                            for (const auto& banner : value.banners) {
                                items.append(
                                    QVariant::fromValue(BannerViewModelReadyDataItem{banner.imageUrl, banner.typeTitle}));
                            }

                            setState(ReadyState{QVariant::fromValue(BannerViewModelReadyData{items})});
                        } else if constexpr (std::is_convertible_v<decltype(value), APIError>) {
                            // errors
                            setState(ErrorState{QStringLiteral("出错了")});
                        }
                    },
                    reply);
            });
        }
    }

    void BannerViewModel::registerMetaTypes() {
        qRegisterMetaType<BannerViewModelReadyDataItem>();
        qRegisterMetaType<BannerViewModelReadyData>();
    }
    void BannerViewModel::componentComplete() {}

} // namespace MusicPlayer::ViewModels
