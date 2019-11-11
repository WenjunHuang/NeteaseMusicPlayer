//
// Created by rick on 2019/11/7.
//

#pragma once

#include "data/error.h"
#include "http.h"
#include "data/dj_banner.h"
#include "data/dj_category_excludehot.h"
#include "data/dj_category_recommend.h"
#include "data/personalized_newsong.h"
#include "data/banner.h"
#include "data/personalized.h"
#include <QFuture>
#include <QJsonDocument>
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <exception>
#include <variant>

namespace MusicPlayer::API {
    template<typename T> using Response = std::variant<Error, T>;
    template<typename T> using APIResponse = QFuture<Response<T>>;

    class MusicAPI {
    public:
        APIResponse<APIDJBannersData> djBanner();

        APIResponse<APIDJCategoryExcludeHotData> djCategoryExcludeHot();

        APIResponse<APIDJCategoryRecommendData> djCategoryRecommend();

        // 首页轮播图
        APIResponse<APIBannersData> banner();

        // 推荐新歌
        APIResponse<APIPersonalizedNewSongData> personalizedNewSong();

        // 推荐歌单
        APIResponse<APIPersonalizedData> personalized(int limit = 30);

        // 用户手机登录
        APIResponse<>
//        async def login_cellphone(self, password: str, phone: str,
//          country_code: Optional[str] = None) -> aiohttp.ClientResponse:
//          password = MD5.new(password.encode('utf-8')).digest().hex()
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
//          cookies = '; '.join([f"{key}={value.value}" for key, value in response.cookies.items()])
//        result = replace(result, cookies=cookies)
//        return result
    };
} // namespace MusicPlayer::MusicAPI

