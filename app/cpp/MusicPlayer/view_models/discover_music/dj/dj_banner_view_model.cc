//
// Created by HUANG WEN JUN on 2019/12/7.
//

#include "dj_banner_view_model.h"
#include "../api/api.h"
#include "../util/util.h"

namespace MusicPlayer::ViewModels {
    using namespace MusicPlayer::API;

    void DJBannerViewModel::registerMetaTypes() {
        qRegisterMetaType<DJBannerViewModelReadyStateData>();
        qRegisterMetaType<DJBannerViewModelReadyStateDataItem>();
    }
    void DJBannerViewModel::reload() {
        if (_loading && !_loading->isReady())
            return;

        setState(LoadingState{});

        MusicAPI api;
        _loading = api.djBanner().via(Util::mainExecutor()).thenValue([this](Response<APIDJBannersData>&& response) {
            std::visit(
                [this](const auto& data) {
                    if constexpr (std::is_convertible_v<decltype(data), APIDJBannersData>) {
                        QVariantList items;
                        for (const auto& item : data.data) {
                            items.append(QVariant::fromValue(DJBannerViewModelReadyStateDataItem{item.pic, item.typeTitle}));
                        }
                        setState(ReadyState{QVariant::fromValue(DJBannerViewModelReadyStateData{items})});
                    } else if constexpr (std::is_convertible_v<decltype(data), APIError>) {
                        auto errorMessage = apiErrorMessage(data);
                        qDebug() << errorMessage;
                        setState(ErrorState{errorMessage});
                    };
                },
                response);

            return std::nullopt;
        });
    }
} // namespace MusicPlayer::ViewModels