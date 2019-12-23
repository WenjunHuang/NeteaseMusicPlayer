//
// Created by HUANG WEN JUN on 2019/11/26.
//
#include "playlist_catlist.h"
#include "../../util/json.h"

namespace MusicPlayer::API {
    APIPlaylistCatListItemData APIPlaylistCatListItemData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<QString>(object.value(QLatin1String("name"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("resourceCount"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("imgId"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("type"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("category"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("resourceType"))),
            Util::fromJsonValue<bool>(object.value(QLatin1String("hot"))),
            Util::fromJsonValue<bool>(object.value(QLatin1String("activity"))),
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
        auto varHash = object.value(QLatin1String("categories")).toObject().toVariantHash();
        for (auto itr = varHash.cbegin(); itr != varHash.cend(); itr++)
            categories.insert(itr.key().toInt(), itr.value().toString());

        return {Util::fromJsonValue<APIPlaylistCatListItemData>(object.value(QLatin1String("all"))),
                Util::fromJsonArray<APIPlaylistCatListItemData>(object.value(QLatin1String("sub"))),
                categories};
    }

    bool APIPlaylistCatListData::operator==(const APIPlaylistCatListData& second) const {
        return all == second.all && sub == second.sub && categories == second.categories;
    }

    bool APIPlaylistCatListData::operator!=(const APIPlaylistCatListData& other) const { return !operator==(other); }
} // namespace MusicPlayer::API
