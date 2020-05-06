//
// Created by rick on 2019/11/7.
//

#include "music_api.h"
#include "util.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QtNetwork>
#include <functional>
#include <variant>

namespace MusicPlayer::API {
    MusicAPI* MusicAPI::instance_ = nullptr;

    using namespace MusicPlayer::Util;

    MusicAPI::MusicAPI() {}

    void MusicAPI::initInstance() {
        if (!instance_) {
            instance_ = new MusicAPI;
        }
    }

    MusicAPI* MusicAPI::instance() {return instance_;}

    void MusicAPI::freeInstance() {
        if (instance_) {
            delete instance_;
            instance_ = nullptr;
        }
    }

    template <typename T> APIResponse<T> parseResponse(MusicHttpResult const& result) {
        if (result.errorString.isEmpty()) {
            QJsonParseError jsonError{};
            auto document = QJsonDocument::fromJson(result.data, &jsonError);
            if (jsonError.error != QJsonParseError::NoError)
                return APIResponse<T>{std::in_place_index<0>, JsonFormatError{jsonError}};
            return APIResponse<T>{std::in_place_index<1>, T::fromJsonValue(document.object())};
        } else {
            return APIResponse<T>(std::in_place_index<0>, NetworkError{result.errorString});
        }
    }

    template <typename T> APIResponseHandler<T>* invoke(std::function<MusicHttpHandler*()> fun) {
        auto handler = fun();

        auto apiResponse = new APIResponseHandler<T>;
        QObject::connect(apiResponse, &APIResponseHandler<T>::finished, &QObject::deleteLater);
        QObject::connect(handler, &MusicHttpHandler::finished, [apiResponse](MusicHttpResult const& result) {
            emit apiResponse->finished(parseResponse<T>(result));
        });
        return apiResponse;
    }

    APIResponseHandler<APIDJBannersData>* MusicAPI::djBanner() {
        return invoke<APIDJBannersData>([]() {
            return MusicHttpWorker::instance()->post(QUrl(QLatin1String("https://music.163.com/weapi/djradio/banner/get")),
                                                     {CryptoType::WEAPI, {QHash<QString, QString>{{"os", "pc"}}}},
                                                     {});
        });
    }

    APIResponseHandler<APIDJCategoryExcludeHotData>* MusicAPI::djCategoryExcludeHot() {
        return invoke<APIDJCategoryExcludeHotData>([]() {
            return MusicHttpWorker::instance()->post(
                QUrl("https://music.163.com/weapi/djradio/category/excludehot"), {CryptoType::WEAPI, {}}, {});
        });
    }

    APIResponseHandler<APIDJCategoryRecommendData>* MusicAPI::djCategoryRecommend() {
        return invoke<APIDJCategoryRecommendData>([]() {
            return MusicHttpWorker::instance()->post(
                QUrl("https://music.163.com/weapi/djradio/home/category/recommend"), {CryptoType::WEAPI, {}}, {});
        });
    }

    APIResponseHandler<APIBannersData>* MusicAPI::banner() {
        return invoke<APIBannersData>([]() {
            return MusicHttpWorker::instance()->post(
                QUrl("https://music.163.com/api/v2/banner/get"), {CryptoType::LINUX_API, {}}, {{"clientType", "pc"}});
        });
    }

    APIResponseHandler<APIPersonalizedNewSongData>* MusicAPI::personalizedNewSong() {
        return invoke<APIPersonalizedNewSongData>([]() {
            return MusicHttpWorker::instance()->post(
                QUrl("https://music.163.com/weapi/personalized/newsong"), {CryptoType::WEAPI, {}}, {{"type", "recommend"}});
        });
    }

    APIResponseHandler<APIPersonalizedData>* MusicAPI::personalized(int limit) {
        return invoke<APIPersonalizedData>([=]() {
            return MusicHttpWorker::instance()->post(QUrl(QLatin1String("https://music.163.com/weapi/personalized/playlist")),
                                                     {CryptoType::WEAPI, {}},
                                                     {{"limit", limit}, {"total", true}, {"n", 1000}});
        });
    }

    APIResponseHandler<APIUserLoginData>* MusicAPI::loginCellphone(const QString& cellphone, const QString& password) {
        QCryptographicHash md5(QCryptographicHash::Md5);
        md5.addData(password.toUtf8());
        QString hashedPassword{md5.result().toHex()};

        auto handler =
            MusicHttpWorker::instance()->post(QUrl("https://music.163.com/weapi/login/cellphone"),
                                              {CryptoType::WEAPI, {}},
                                              {{"phone", cellphone}, {"password", hashedPassword}, {"rememberLogin", "true"}});
        auto apiResponse = new APIResponseHandler<APIUserLoginData>;
        QObject::connect(apiResponse, &APIResponseHandler<APIUserLoginData>::finished, &QObject::deleteLater);
        QObject::connect(handler, &MusicHttpHandler::finished, [apiResponse](MusicHttpResult const& result) {
            auto parsed  = parseResponse<APIUserLoginData>(result);
            auto visited = std::visit(
                [=](auto value) -> APIResponse<APIUserLoginData> {
                    if constexpr (std::is_convertible_v<decltype(value), APIUserLoginData>) {
                        auto cookies = result.reply->header(QNetworkRequest::SetCookieHeader).value<QList<QNetworkCookie>>();
                        auto cookieToken = std::accumulate(
                            cookies.cbegin(), cookies.cend(), QString(), [](const auto& accum, const auto& cookie) {
                                return QString("%1; %2=%3").arg(accum, cookie.name(), cookie.value());
                            });
                        value.cookieToken = cookieToken;
                    }
                    return value;
                },
                parsed);
            emit apiResponse->finished(visited);
        });
        return apiResponse;
    }

    APIResponseHandler<APIUserPrivateMessagesData>*
    MusicAPI::userPrivateMessages(const QString& cookieToken, int limit, int offset) {
        return invoke<APIUserPrivateMessagesData>([=]() {
            return MusicHttpWorker::instance()->post(QUrl("https://music.163.com/weapi/msg/private/users"),
                                                     {CryptoType::WEAPI, cookieToken},
                                                     {{"offset", offset}, {"limit", limit}, {"total", "true"}});
        });
    }

    APIResponseHandler<APIPlaylistCatListData>* MusicAPI::playlistCatlist() {
        return invoke<APIPlaylistCatListData>([]() {
            return MusicHttpWorker::instance()->post(
                QUrl("https://music.163.com/weapi/playlist/catalogue"), {CryptoType::WEAPI}, {});
        });
    }

    APIResponseHandler<APITopPlayListData>* MusicAPI::topPlaylistHighQuality(const QString& cat, int limit, qint64 before) {
        return invoke<APITopPlayListData>([=]() {
            return MusicHttpWorker::instance()->post(QUrl("https://music.163.com/weapi/playlist/highquality/list"),
                                                     {CryptoType::WEAPI},
                                                     {{"cat", cat}, {"limit", limit}, {"lasttime", before}, {"total", true}});
        });
    }

    APIResponseHandler<APIPlayListDetailData>* MusicAPI::playlistDetail(int playlistId) {
        return invoke<APIPlayListDetailData>([=]() {
            return MusicHttpWorker::instance()->post(QUrl("https://music.163.com/weapi/v3/playlist/detail"),
                                                     {CryptoType::WEAPI},
                                                     {{"id", playlistId}, {"n", 100000}, {"s", 8}});
        });
    }

    APIResponseHandler<APITopPlayListData>* MusicAPI::topPlaylist(const QString& cat, int limit, int offset) {
        return invoke<APITopPlayListData>([=]() {
            return MusicHttpWorker::instance()->post(
                QUrl("https://music.163.com/weapi/playlist/list"),
                {CryptoType::WEAPI},
                {{"cat", cat}, {"limit", limit}, {"offset", offset}, {"order", "hot"}, {"total", true}});
        });
    }

    APIResponseHandler<APIDJCategoryListData>* MusicAPI::djCatList() {
        return invoke<APIDJCategoryListData>([]() {
            return MusicHttpWorker::instance()->post(
                QUrl("https://music.163.com/weapi/djradio/category/get"), {CryptoType::WEAPI}, {});
        });
    }

    APIResponseHandler<QString>* MusicAPI::songDetail(const QVector<int>& songIds) {
        QVariantList c;
        QVariantList ids;
        for (const auto& songId : songIds) {
            QVariantHash map;
            map.insert("id", songId);
            c.append(map);

            ids.append(songId);
        }
        QString cstr{QJsonDocument(QJsonArray::fromVariantList(c)).toJson(QJsonDocument::Compact)};
        QString idsstr{QJsonDocument(QJsonArray::fromVariantList(ids)).toJson(QJsonDocument::Compact)};

        return new APIResponseHandler<QString>;
        //        return invoke<QString>MusicHttpWorker::instance()
        //            ->post(QUrl("https://music.163.com/weapi/v3/song/detail"), {CryptoType::WEAPI}, {{"c", cstr}, {"ids",
        //            idsstr}}) .via(Util::cpuExecutor()) .thenValue([](QNetworkReply* reply) { return
        //            APIResponse<QString>{QString(reply->readAll())}; });
    }

    APIResponseHandler<APISongUrlData>* MusicAPI::songUrl(SongId songId, SongQuality songQuality) {
        QString idsstr{
            QJsonDocument(QJsonArray::fromVariantList(QVariantList{QVariant(songId)})).toJson(QJsonDocument::Compact)};
        int br;
        if (songQuality == SongQuality::Q96000)
            br = 96000;
        if (songQuality == SongQuality::Q160000)
            br = 160000;
        if (songQuality == SongQuality::Q320000)
            br = 320000;
        if (songQuality == SongQuality::Q990000)
            br = 990000;
        return invoke<APISongUrlData>([=]() {
            return MusicHttpWorker::instance()->post(QUrl("https://music.163.com/weapi/song/enhance/player/url"),
                                                     {CryptoType::WEAPI},
                                                     {{"ids", idsstr}, {"br", QString("%1").arg(br)}});
        });
    }

    APIResponseHandler<QString>* MusicAPI::artistDesc(int artistId) {
        //        return MusicHttpWorker::instance()
        //            ->post(QUrl("https://music.163.com/weapi/artist/introduction"), {CryptoType::WEAPI}, {{"id", artistId}})
        //            .via(Util::cpuExecutor())
        //            .thenValue([](QNetworkReply* reply) { return APIResponse<QString>{QString(reply->readAll())}; });
        return new APIResponseHandler<QString>;
    }
} // namespace MusicPlayer::API
