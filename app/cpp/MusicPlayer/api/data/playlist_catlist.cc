//
// Created by HUANG WEN JUN on 2019/11/26.
//
#include "playlist_catlist.h"
#include "../../util/json.h"

namespace MusicPlayer::API {
    APIPlaylistCatListItemData APIPlaylistCatListItemData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("name"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("resourceCount"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("imgId"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("category"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("category"))),
            Util::fromJsonValue<bool>(object.value(QLatin1Literal("hot"))),
            Util::fromJsonValue<bool>(object.value(QLatin1Literal("activity"))),
        };
    }

    bool APIPlaylistCatListItemData::operator==(const APIPlaylistCatListItemData& second) const {
        return name == second.name && resourceCount == second.resourceCount && imgId == second.imgId && type == second.type &&
               category == second.category && resourceType == second.resourceType && hot == second.hot &&
               activity == second.activity;
    }

    bool APIPlaylistCatListItemData::operator!=(const APIPlaylistCatListItemData& second) const { return !operator==(second); }

    APIPlaylistCatListData APIPlaylistCatListData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();

        QHash<int, QString> categories;
        auto varHash = object.value(QLatin1Literal("categories")).toObject().toVariantHash();
        for (auto itr = varHash.cbegin(); itr != varHash.cend(); itr++)
            categories.insert(itr.key().toInt(), itr.value().toString());

        return {Util::fromJsonValue<APIPlaylistCatListItemData>(object.value(QLatin1Literal("all"))),
                Util::fromJsonArray<APIPlaylistCatListItemData>(object.value(QLatin1Literal("sub"))),
                categories};
    }

    bool APIPlaylistCatListData::operator==(const APIPlaylistCatListData& second) const {
        return all == second.all && sub == second.sub && categories == second.categories;
    }

    bool APIPlaylistCatListData::operator!=(const APIPlaylistCatListData& other) const { return !operator==(other); }
} // namespace MusicPlayer::API
