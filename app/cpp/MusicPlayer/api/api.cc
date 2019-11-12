//
// Created by rick on 2019/11/7.
//

#include "api.h"
#include "../asyncfuture.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QtNetwork>
#include <variant>

using namespace AsyncFuture;
namespace MusicPlayer::API {
    template <typename T> APIResponse<T> parseResponse(QNetworkReply* reply) {
        auto fun = [reply]() {
            auto statusCode =
                reply->attribute(QNetworkRequest::HttpStatusCodeAttribute)
                    .toInt();
            if (statusCode == 200) {
                QJsonParseError jsonError;
                auto document =
                    QJsonDocument::fromJson(reply->readAll(), &jsonError);
                if (jsonError.error != QJsonParseError::NoError)
                    return Response<T>{std::in_place_index<0>,
                                       JsonFormatError{jsonError}};
                return Response<T>{std::in_place_index<1>,
                                   T::fromJsonValue(document.object())};
            } else {
                return Response<T>(std::in_place_index<0>,
                                   NetworkError{reply->errorString()});
            }
        };
        return QtConcurrent::run(fun);
    }

    APIResponse<APIDJBannersData> MusicAPI::djBanner() {
        QUrl url("https://music.163.com/weapi/djradio/banner/get");
        auto response = HttpWorker::instance()->post(
            url, {CryptoType::WEAPI, {QHash<QString, QString>{{"os", "pc"}}}},
            {});

        return AsyncFuture::observe(response)
            .subscribe([this](QNetworkReply* reply) {
                return parseResponse<APIDJBannersData>(reply);
            })
            .future();
    }

    APIResponse<APIDJCategoryExcludeHotData> MusicAPI::djCategoryExcludeHot() {
        QUrl url("https://music.163.com/weapi/djradio/category/excludehot");
        auto response =
            HttpWorker::instance()->post(url, {CryptoType::WEAPI, {}}, {});
        return AsyncFuture::observe(response)
            .subscribe([this](QNetworkReply* reply) {
                return parseResponse<APIDJCategoryExcludeHotData>(reply);
            })
            .future();
    }

    APIResponse<APIDJCategoryRecommendData> MusicAPI::djCategoryRecommend() {
        QUrl url("https://music.163.com/weapi/djradio/home/category/recommend");
        auto response =
            HttpWorker::instance()->post(url, {CryptoType::WEAPI, {}}, {});
        return AsyncFuture::observe(response)
            .subscribe([this](QNetworkReply* reply) {
                return parseResponse<APIDJCategoryRecommendData>(reply);
            })
            .future();
    }

    APIResponse<APIBannersData> MusicAPI::banner() {
        QUrl url("https://music.163.com/api/v2/banner/get");
        auto response = HttpWorker::instance()->post(
            url, {CryptoType::LINUX_API, {}}, {{"clientType", "pc"}});
        return AsyncFuture::observe(response)
            .subscribe([this](QNetworkReply* reply) {
                return parseResponse<APIBannersData>(reply);
            })
            .future();
    }

    APIResponse<APIPersonalizedNewSongData> MusicAPI::personalizedNewSong() {
        QUrl url("https://music.163.com/weapi/personalized/newsong");
        auto response = HttpWorker::instance()->post(
            url, {CryptoType::WEAPI, {}}, {{"type", "recommend"}});
        return AsyncFuture::observe(response)
            .subscribe([this](QNetworkReply* reply) {
                return parseResponse<APIPersonalizedNewSongData>(reply);
            })
            .future();
    }

    APIResponse<APIPersonalizedData> MusicAPI::personalized(int limit) {
        QUrl url("https://music.163.com/weapi/personalized/playlist");
        auto response = HttpWorker::instance()->post(
            url, {CryptoType::WEAPI, {}},
            {{"limit", limit}, {"total", true}, {"n", 1000}});
        return AsyncFuture::observe(response)
            .subscribe([this](QNetworkReply* reply) {
                return parseResponse<APIPersonalizedData>(reply);
            })
            .future();
    }

    APIResponse<APIUserLoginData>
    MusicAPI::loginCellphone(const QString& cellphone,
                             const QString& password) {

        //        async def login_cellphone(self, password: str, phone: str,
        //          country_code: Optional[str] = None) ->
        //          aiohttp.ClientResponse: password =
        //          MD5.new(password.encode('utf-8')).digest().hex()
        //        response = await request(self._http_session,
        //        HTTPMethod.POST,
        //        "https://music.163.com/weapi/login/cellphone",
        //        {
        //          "phone": phone,
        //            "countrycode": country_code,
        //            "password": password,
        //            "remberLogin": "true"
        //        },
        //        RequestOption(crypto=CryptoType.WEAPI, cookie={
        //          "os": "pc"
        //        }))
        //        result = await parse_response(response, APIUserLoginData)
        //        if type(result) == APIUserLoginData:
        //          cookies = '; '.join([f"{key}={value.value}" for key, value
        //          in response.cookies.items()])
        //        result = replace(result, cookies=cookies)
        //        return result
        QCryptographicHash md5(QCryptographicHash::Md5);
        md5.addData(password.toUtf8());
        QString hashedPassword{md5.result().toHex()};

        QUrl url("https://music.163.com/weapi/login/cellphone");
        auto response =
            HttpWorker::instance()->post(url, {CryptoType::WEAPI, {}},
                                         {{"phone", cellphone},
                                          {"password", hashedPassword},
                                          {"remberLogin", "true"}});
        return AsyncFuture::observe(response)
            .subscribe([this](QNetworkReply* reply) {
                return observe(parseResponse<APIUserLoginData>(reply))
                    .subscribe([=](Response<APIUserLoginData> response)
                                   -> Response<APIUserLoginData> {
                        std::visit(
                            [=](auto& value) {
                                if constexpr (std::is_convertible_v<
                                                  decltype(value),
                                                  APIUserLoginData>) {
                                    auto cookies =
                                        reply
                                            ->header(QNetworkRequest::
                                                         SetCookieHeader)
                                            .value<QList<QNetworkCookie>>();
                                    auto cookieToken = std::accumulate(
                                        cookies.cbegin(), cookies.cend(),
                                        QString(),
                                        [](const auto& accum,
                                           const auto& cookie) {
                                            return QString("%1; %2=%3")
                                                .arg(accum, cookie.name(),
                                                     cookie.value());
                                        });
                                    value.cookieToken = cookieToken;
                                } else { }
                            },
                            response);
                        return response;
                    })
                    .future();
            })
            .future();
    }

} // namespace MusicPlayer::API
