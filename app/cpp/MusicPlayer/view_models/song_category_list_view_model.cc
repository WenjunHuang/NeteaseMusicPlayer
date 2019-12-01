//
// Created by rick on 2019/11/13.
//

#include "song_category_list_view_model.h"

namespace MusicPlayer::ViewModels {
    bool LoadingState::operator==(const MusicPlayer::ViewModels::LoadingState& other) const { return true; }

    bool LoadingState::operator!=(const LoadingState& other) const { return false; }

    bool ErrorState::operator==(const ErrorState& other) const { return message == other.message; }

    bool ErrorState::operator!=(const ErrorState& other) const { return !operator==(other); }

    bool ReadyStateItem::operator==(const ReadyStateItem& other) const {
        return name == other.name && icon == other.icon && subCats == other.subCats;
    }

    bool ReadyStateItem::operator!=(const ReadyStateItem& other) const { return !operator==(other); }

    bool ReadyState::operator==(const ReadyState& other) const { return allName == other.allName && items == other.items; }

    bool ReadyState::operator!=(const ReadyState& other) const { return !operator==(other); }

    void SongCategoryListViewModel::reload() {
        if (std::get_if<LoadingState>(&_state)) {
            // 正在加载中....
            return;
        }

        setState(LoadingState{});
        SongCategoryRepository::instance()
            ->getPlaylistCatListData()
            .via(mainExecutor())
            .thenValue([this](const Response<APIPlaylistCatListData>& reply) {
                std::visit(
                    [this](auto& value) {
                        if constexpr (std::is_convertible_v<decltype(value), APIPlaylistCatListData>) {
                            QString allName = value.all.name;

                            QMultiHash<int, QVariant> catItems;
                            for (auto sub = value.sub.cbegin(); sub != value.sub.cend(); sub++) {
                                auto item = (*sub).template value<APIPlaylistCatListItemData>();
                                catItems.insert(item.category, QVariant::fromValue(item));
                            }

                            QVariantList readyStateItems;
                            for (auto cat = value.categories.cbegin(); cat != value.categories.cend(); cat++) {
                                int catCode     = cat.key().toInt();
                                QString catName = cat.value().toString();

                                readyStateItems.append(QVariant::fromValue(ReadyStateItem{
                                    catName, QString("category_icon_%1").arg(catCode), catItems.values(catCode)}));
                            }

                            setState(ReadyState{allName, readyStateItems});
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

    void SongCategoryListViewModel::setState(const State& state) {
        if (state == _state)
            return;
        _state = state;
        emit stateChanged();
    }
    void SongCategoryListViewModel::componentComplete() {
        reload();
    }
} // namespace MusicPlayer::ViewModels
