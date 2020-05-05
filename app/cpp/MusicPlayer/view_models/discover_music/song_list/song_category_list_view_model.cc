//
// Created by rick on 2019/11/13.
//

#include "song_category_list_view_model.h"

namespace MusicPlayer::ViewModels {

    void SongCategoryListViewModel::reload() {
        if (std::get_if<LoadingState>(&_state)) {
            // 正在加载中....
            return;
        }

        setState(LoadingState{});
        MusicAPI api;
        auto response = api.playlistCatlist();
        connect(response,&APIResponseHandler<APIPlaylistCatListData>::finished,[this](const APIResponse<APIPlaylistCatListData>& reply) {
                std::visit(
                    [this](auto& value) {
                        if constexpr (std::is_convertible_v<decltype(value), APIPlaylistCatListData>) {
                            QString allName = value.all.name;
                            QVector<QString> hotCategories;

                            QMultiHash<int, QVariant> catItems;
                            for (const auto& sub : value.sub) {
                                catItems.insert(
                                    sub.category,
                                    QVariant::fromValue(SongCategoryListViewModelReadyStateCategoryItem{sub.name, sub.hot}));

                                if (sub.hot)
                                    hotCategories.append(sub.name);
                            }

                            QVariantList readyStateItems;
                            auto keys = value.categories.keys();
                            std::sort(
                                keys.begin(), keys.end(), [](const auto& first, const auto& second) { return first < second; });

                            for (const auto& catCode : keys) {
                                readyStateItems.append(QVariant::fromValue(SongCategoryListViewModelReadyStateCategory{
                                    value.categories.value(catCode),
                                    catCode,
                                    catItems.values(catCode),
                                }));
                            }

                            setState(ReadyState{QVariant::fromValue(
                                SongCategoryListViewModelReadyState{allName, readyStateItems, hotCategories})});
                        } else {
                            // errors
                            auto errorMessage = std::visit(
                                [this](const auto& error) {
                                    if constexpr (std::is_convertible_v<decltype(error), ErrorResponseError>) {
                                        return error.message.value_or(QString(""));
                                    } else if constexpr (std::is_convertible_v<decltype(error), NetworkError>) {
                                        return error.message;
                                    } else if constexpr (std::is_convertible_v<decltype(error), JsonFormatError>) {
                                        return error.parseError.errorString();
                                    }
                                },
                                value);
                            setState(ErrorState{errorMessage});
                        }
                    },
                    reply);
            });
    }

    void SongCategoryListViewModel::componentComplete() { reload(); }

    void SongCategoryListViewModel::registerMetaTypes() {
        qRegisterMetaType<SongCategoryListViewModelReadyStateCategory>();
        qRegisterMetaType<SongCategoryListViewModelReadyState>();
        qRegisterMetaType<SongCategoryListViewModelReadyStateCategoryItem>();
    }

    bool SongCategoryListViewModelReadyStateCategoryItem::operator==(
        const SongCategoryListViewModelReadyStateCategoryItem& other) const {
        return name == other.name && hot == other.hot;
    }
    bool SongCategoryListViewModelReadyStateCategoryItem::operator!=(
        const SongCategoryListViewModelReadyStateCategoryItem& other) const {
        return !operator==(other);
    }
    bool
    SongCategoryListViewModelReadyStateCategory::operator==(const SongCategoryListViewModelReadyStateCategory& other) const {
        return name == other.name && category == other.category && items == other.items;
    }
    bool
    SongCategoryListViewModelReadyStateCategory::operator!=(const SongCategoryListViewModelReadyStateCategory& other) const {
        return !operator==(other);
    }
    bool SongCategoryListViewModelReadyState::operator==(const SongCategoryListViewModelReadyState& other) const {
        return allName == other.allName && categories == other.categories;
    }
    bool SongCategoryListViewModelReadyState::operator!=(const SongCategoryListViewModelReadyState& other) const {
        return !operator==(other);
    }
} // namespace MusicPlayer::ViewModels
