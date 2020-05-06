//
// Created by HUANG WEN JUN on 2019/12/7.
//

#include "dj_banner_view_model.h"

namespace MusicPlayer::ViewModel {
    using namespace MusicPlayer::API;

    void DJBannerViewModel::registerMetaTypes() {
        qRegisterMetaType<DJBannerViewModelReadyStateData>();
        qRegisterMetaType<DJBannerViewModelReadyStateDataItem>();
    }
    void DJBannerViewModel::reload() {
        if (std::get_if<LoadingState>(&_state))
            return;

        setState(LoadingState{});

        auto api = MusicAPI::instance();
        auto response = api->djBanner();
        connect(response,&APIResponseHandler<APIDJBannersData>::finished,[this](const APIResponse<APIDJBannersData>& response) {
            std::visit(
                overload{
                    [this](const APIDJBannersData& data) {
                        QVariantList items;
                        for (const auto& item : data.data) {
                            items.append(QVariant::fromValue(DJBannerViewModelReadyStateDataItem{item.pic, item.typeTitle}));
                        }
                        setState(ReadyState{QVariant::fromValue(DJBannerViewModelReadyStateData{items})});
                    },
                    [this](const APIError& error) {
                        auto errorMessage = apiErrorMessage(error);
                        qDebug() << errorMessage;
                        setState(ErrorState{errorMessage});
                    },
                },
                response);
        });
    }
} // namespace MusicPlayer::ViewModels