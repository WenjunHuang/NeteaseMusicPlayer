//
// Created by rick on 2019/11/7.
//

#include "api.h"
#include "../util/executor.h"
#include "../util/misc.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QtNetwork>
#include <iostream>
#include <variant>

// using namespace AsyncFuture;
namespace MusicPlayer::API {
    using namespace MusicPlayer::Util;
    template <typename T> Response<T> parseResponse(QNetworkReply* reply) {
        //        auto fun = [reply]() {
        auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (statusCode == 200) {
            QJsonParseError jsonError;
            auto document = QJsonDocument::fromJson(reply->readAll(), &jsonError);
            if (jsonError.error != QJsonParseError::NoError)
                return Response<T>{std::in_place_index<0>, JsonFormatError{jsonError}};
            return Response<T>{std::in_place_index<1>, T::fromJsonValue(document.object())};
        } else {
            return Response<T>(std::in_place_index<0>, NetworkError{reply->errorString()});
        }
        //        };
        //        return folly::makeSemiFutureWith(fun);
        //        return QtConcurrent::run(fun);
    }

    APIResponse<APIDJBannersData> MusicAPI::djBanner() {
        return HttpWorker::instance()
            ->post(QUrl(QLatin1Literal("https://music.163.com/weapi/djradio/banner/get")),
                   {CryptoType::WEAPI, {QHash<QString, QString>{{"os", "pc"}}}},
                   {})
            .via(AppExecutor::instance()->getCPUExecutor().get())
            .thenValue([](QNetworkReply* reply) {
                auto threadId = std::this_thread::get_id();
                std::cout << "parseResponse:" << threadId << std::endl;

                DeleteLater guard(reply);
                return parseResponse<APIDJBannersData>(reply);
            });
    }

    APIResponse<APIDJCategoryExcludeHotData> MusicAPI::djCategoryExcludeHot() {
        return HttpWorker::instance()
            ->post(QUrl("https://music.163.com/weapi/djradio/category/excludehot"), {CryptoType::WEAPI, {}}, {})
            .via(Util::AppExecutor::instance()->getCPUExecutor().get())
            .thenValue([](QNetworkReply* reply) { return parseResponse<APIDJCategoryExcludeHotData>(reply); });
    }

    APIResponse<APIDJCategoryRecommendData> MusicAPI::djCategoryRecommend() {
        return HttpWorker::instance()
            ->post(QUrl("https://music.163.com/weapi/djradio/home/category/recommend"), {CryptoType::WEAPI, {}}, {})
            .via(Util::AppExecutor::instance()->getCPUExecutor().get())
            .thenValue([](QNetworkReply* reply) { return parseResponse<APIDJCategoryRecommendData>(reply); });
    }

    APIResponse<APIBannersData> MusicAPI::banner() {
        return HttpWorker::instance()
            ->post(QUrl("https://music.163.com/api/v2/banner/get"), {CryptoType::LINUX_API, {}}, {{"clientType", "pc"}})
            .via(Util::AppExecutor::instance()->getCPUExecutor().get())
            .thenValue([this](QNetworkReply* reply) { return parseResponse<APIBannersData>(reply); });
    }

    APIResponse<APIPersonalizedNewSongData> MusicAPI::personalizedNewSong() {
        return HttpWorker::instance()
            ->post(QUrl("https://music.163.com/weapi/personalized/newsong"), {CryptoType::WEAPI, {}}, {{"type", "recommend"}})
            .via(Util::AppExecutor::instance()->getCPUExecutor().get())
            .thenValue([this](QNetworkReply* reply) { return parseResponse<APIPersonalizedNewSongData>(reply); });
    }

    APIResponse<APIPersonalizedData> MusicAPI::personalized(int limit) {
        return HttpWorker::instance()
            ->post(QUrl(QLatin1Literal("https://music.163.com/weapi/personalized/playlist")),
                   {CryptoType::WEAPI, {}},
                   {{"limit", limit}, {"total", true}, {"n", 1000}})
            .via(Util::AppExecutor::instance()->getCPUExecutor().get())
            .thenValue([this](QNetworkReply* reply) { return parseResponse<APIPersonalizedData>(reply); });
    }

    APIResponse<APIUserLoginData> MusicAPI::loginCellphone(const QString& cellphone, const QString& password) {
        QCryptographicHash md5(QCryptographicHash::Md5);
        md5.addData(password.toUtf8());
        QString hashedPassword{md5.result().toHex()};

        return HttpWorker::instance()->post(QUrl("https://music.163.com/weapi/login/cellphone"),
                   {CryptoType::WEAPI, {}},
                   {{"phone", cellphone}, {"password", hashedPassword}, {"remberLogin", "true"}})
            .via(Util::AppExecutor::instance()->getCPUExecutor().get())
            .thenValue([](QNetworkReply* reply) -> Response<APIUserLoginData> {
                auto result = parseResponse<APIUserLoginData>(reply);
                return std::visit(
                    [=](auto value) -> Response<APIUserLoginData> {
                        if constexpr (std::is_convertible_v<decltype(value), APIUserLoginData>) {
                            auto cookies     = reply->header(QNetworkRequest::SetCookieHeader).value<QList<QNetworkCookie>>();
                            auto cookieToken = std::accumulate(
                                cookies.cbegin(), cookies.cend(), QString(), [](const auto& accum, const auto& cookie) {
                                    return QString("%1; %2=%3").arg(accum, cookie.name(), cookie.value());
                                });
                            value.cookieToken = cookieToken;
                        }
                        return value;
                    },
                    result);
            });
    }

    APIResponse<APIUserPrivateMessagesData> MusicAPI::userPrivateMessages(const QString& cookieToken, int limit, int offset) {
        return HttpWorker::instance()->post(QUrl("https://music.163.com/weapi/msg/private/users"),
                   {CryptoType::WEAPI, cookieToken},
                   {{"offset", offset}, {"limit", limit}, {"total", "true"}})
            .via(Util::AppExecutor::instance()->getCPUExecutor().get())
            .thenValue([](QNetworkReply* reply) { return parseResponse<APIUserPrivateMessagesData>(reply); });
    }

    APIResponse<APIPlaylistCatListData> MusicAPI::playlistCatlist() {
        return HttpWorker::instance()->post(QUrl("https://music.163.com/weapi/playlist/catalogue"), {CryptoType::WEAPI}, {})
            .via(Util::AppExecutor::instance()->getCPUExecutor().get())
            .thenValue([](QNetworkReply* reply) { return parseResponse<APIPlaylistCatListData>(reply); });
    }

    void MusicAPI::registerTypes() {
        //        qRegisterMetaType<MusicPlayer::API::APIBannerData>();
    }

} // namespace MusicPlayer::API
