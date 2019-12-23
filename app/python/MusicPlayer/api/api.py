import json
from typing import Union, Optional, List, Iterable

import aiohttp
from typing_extensions import Literal
from Cryptodome.Hash import MD5
from dataclasses import replace

from MusicPlayer.api.data.album import APIAlbumDynamicData, APIAlbumNewestData, APIAlbumSubscriptionListData, \
    APIAlbumInfoData, APIArtistAlbumData
from MusicPlayer.api.data.artist import APIArtistDescData, APIArtistListData
from MusicPlayer.api.data.artist_songs import APIArtistSongsData
from MusicPlayer.api.data.banner import APIBannersData
from MusicPlayer.api.data.dj_banner import APIDJBannersData
from MusicPlayer.api.data.dj_category import APIDJCategoryExcludeHotData, APIDJCategoryRecommendData, \
    APIDJCategoryListData
from MusicPlayer.api.data.mv import APIArtistMVsData, APIMVAllData, APIMVDetailData, APIMVUrlData
from MusicPlayer.api.data.personalized import APIPersonalizedData
from MusicPlayer.api.data.personalized_mv import APIPersonalizedMVData
from MusicPlayer.api.data.personalized_newsong import APIPersonalizedNewSongData
from MusicPlayer.api.data.playlist_catlist import APIPlaylistCatListData
from MusicPlayer.api.data.user_login import APIUserLoginData
from MusicPlayer.api.data.user_private_message import APIUserPrivateMessagesData
from MusicPlayer.api.error import APIError
from MusicPlayer.api.http import request, HTTPMethod, RequestOption, CryptoType
from MusicPlayer.api.parse_response import parse_response


class API:
    def __init__(self, http_session: aiohttp.ClientSession):
        self._http_session = http_session

    async def dj_banner(self) -> Union[APIError, APIDJBannersData]:
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 "https://music.163.com/weapi/djradio/banner/get",
                                 {},
                                 RequestOption(crypto=CryptoType.WEAPI, cookie={"os": "pc"}))
        return await parse_response(response, APIDJBannersData)

    async def dj_category_excludehot(self) -> Union[APIError, APIDJCategoryExcludeHotData]:
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 "https://music.163.com/weapi/djradio/category/excludehot",
                                 {},
                                 RequestOption(crypto=CryptoType.WEAPI))
        return await parse_response(response, APIDJCategoryExcludeHotData)

    async def dj_category_recommend(self):
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 "https://music.163.com/weapi/djradio/home/category/recommend",
                                 {},
                                 RequestOption(crypto=CryptoType.WEAPI))
        return await parse_response(response, APIDJCategoryRecommendData)

    async def dj_catelist(self):
        # 电台分类列表
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 "https://music.163.com/weapi/djradio/category/get",
                                 {},
                                 RequestOption(crypto=CryptoType.WEAPI))
        return await parse_response(response, APIDJCategoryListData)

    async def dj_hot(self, limit: int, offset: int):
        # 热门电台
        return await request(self._http_session,
                             HTTPMethod.POST,
                             "https://music.163.com/weapi/djradio/hot/v1",
                             {'limit': limit, 'offset': offset},
                             RequestOption(crypto=CryptoType.WEAPI))

    async def dj_detail(self, rid: str):
        # 电台详情
        return await request(self._http_session,
                             HTTPMethod.POST,
                             "https://music.163.com/weapi/djradio/get",
                             {'id': rid},
                             RequestOption(crypto=CryptoType.WEAPI))

    async def dj_paygift(self, limit: int, offset: int):
        # 付费电台
        return await request(self._http_session,
                             HTTPMethod.POST,
                             "https://music.163.com/weapi/djradio/home/paygift/list?_nmclfl=1",
                             {"limit": limit, "offset": offset},
                             RequestOption(crypto=CryptoType.WEAPI))

    async def dj_program_detail(self, pid: str):
        # 电台节目详情
        return await request(self._http_session,
                             HTTPMethod.POST,
                             "https://music.163.com/weapi/dj/program/detail",
                             {'id': pid},
                             RequestOption(crypto=CryptoType.WEAPI))

    async def dj_program_toplist(self, limit: int, offset: int):
        # 电台节目详情
        return await request(self._http_session,
                             HTTPMethod.POST,
                             "https://music.163.com/api/program/toplist/v1",
                             {"limit": limit, "offset": 0},
                             RequestOption(crypto=CryptoType.WEAPI))

    async def dj_program(self, radio_id: str, limit: int, offset: int, asc: bool):
        # 电台节目列表
        return await request(self._http_session,
                             HTTPMethod.POST,
                             "https://music.163.com/weapi/dj/program/byradio",
                             {"radioId": radio_id,
                              "limit": limit,
                              "offset": offset,
                              "asc": asc},
                             RequestOption(crypto=CryptoType.WEAPI))

    async def dj_radio_hot(self, cat_id: Union[str, int], limit: int, offset: int):
        # 类别热门电台
        return await request(self._http_session,
                             HTTPMethod.POST,
                             "https://music.163.com/api/djradio/hot",
                             {"cateId": cat_id,
                              "limit": limit,
                              "offset": offset},
                             RequestOption(crypto=CryptoType.WEAPI))

    async def dj_recommend_type(self, cat_id: Union[str, int]):
        # 精选电台分类
        #   有声书 10001
        #   知识技能 453050
        #   商业财经 453051
        #   人文历史 11
        #   外语世界 13
        #   亲子宝贝 14
        #   创作|翻唱 2001
        #   音乐故事 2
        #   3D|电子 10002
        #   相声曲艺 8
        #   情感调频 3
        #   美文读物 6
        #   脱口秀 5
        #   广播剧 7
        #   二次元 3001
        #   明星做主播 1
        #   娱乐|影视 4
        #   科技科学 453052
        #   校园|教育 4001
        #   旅途|城市 12

        return await request(self._http_session,
                             HTTPMethod.POST,
                             "https://music.163.com/weapi/djradio/recommend",
                             {"cateId": cat_id},
                             RequestOption(crypto=CryptoType.WEAPI))

    async def dj_recommend(self):
        # 精选电台
        return await request(self._http_session,
                             HTTPMethod.POST,
                             "https://music.163.com/weapi/djradio/recommend/v1",
                             {},
                             RequestOption(crypto=CryptoType.WEAPI))

    # async def dj_sub(self,rid:Union[str,int]):
    #     # 订阅与取消电台
    #     return await request(self._http_session,
    #                          HTTPMethod.POST,
    #                          "https://music.163.com/weapi/djradio/{",
    #                          {},
    #                          RequestOption(crypto=CryptoType.WEAPI))

    async def dj_today_perfered(self, page: int = 0):
        # dj今日优选
        return await request(self._http_session,
                             HTTPMethod.POST,
                             "http://music.163.com/weapi/djradio/home/today/perfered",
                             {"page": page},
                             RequestOption(crypto=CryptoType.WEAPI))

    async def dj_toplist(self, limit: int, offset: 0, type_: Union[Literal[0], Literal[1]]):
        # 新晋电台榜/热门电台榜
        # 0为新晋,1为热门
        return await request(self._http_session,
                             HTTPMethod.POST,
                             "https://music.163.com/api/djradio/toplist",
                             {"limit": limit, "offset": offset, "type": type_},
                             RequestOption(crypto=CryptoType.WEAPI))

    async def login_cellphone(self, password: str, phone: str,
                              country_code: Optional[str] = None) -> aiohttp.ClientResponse:
        password = MD5.new(password.encode('utf-8')).digest().hex()
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 "https://music.163.com/weapi/login/cellphone",
                                 {
                                     "phone": phone,
                                     "countrycode": country_code,
                                     "password": password,
                                     "remberLogin": "true"
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI, cookie={
                                     "os": "pc"
                                 }))
        result = await parse_response(response, APIUserLoginData)
        if type(result) == APIUserLoginData:
            cookies = '; '.join([f"{key}={value.value}" for key, value in response.cookies.items()])
            result = replace(result, cookies=cookies)
        return result

    async def user_event(self, uid: str, limit: int):
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/event/get/{uid}",
                                 {
                                     "getcounts": True,
                                     "time": -1,
                                     "limit": limit,
                                     "total": False
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI))
        return response

    async def msg_private(self, auth_cookie: str, limit: int, offset: int):
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/msg/private/users",
                                 {
                                     "offset": offset,
                                     "limit": limit,
                                     "total": "true"
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI,
                                               cookie=auth_cookie))
        result = await parse_response(response, APIUserPrivateMessagesData)
        return result

    async def album_detail_dynamic(self, album_id: int):
        # 专辑动态信息
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/album/detail/dynamic",
                                 {
                                     "id": album_id
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI))
        return await parse_response(response, APIAlbumDynamicData)

    async def album_newest(self):
        # 最新专辑
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/discovery/newAlbum",
                                 {},
                                 RequestOption(crypto=CryptoType.WEAPI))
        return await parse_response(response, APIAlbumNewestData)

    async def album_sublist(self, auth_cookies: str, limit: int = 30, offset: int = 0):
        # 已经收藏专辑列表
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/album/sublist",
                                 {
                                     "limit": limit,
                                     "offset": offset,
                                     "total": True
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI, cookie=auth_cookies))
        return await parse_response(response, APIAlbumSubscriptionListData)

    async def album(self, album_id: int):
        # 专辑内容
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/v1/album/{album_id}",
                                 {},
                                 RequestOption(crypto=CryptoType.WEAPI))
        return await parse_response(response, APIAlbumInfoData)

    async def artist_album(self, artist_id: int, limit: int = 30, offset: int = 0):
        # 歌手专辑列表
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/artist/albums/{artist_id}",
                                 {
                                     "limit": limit,
                                     "offset": offset,
                                     "total": True
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI))
        return await parse_response(response, APIArtistAlbumData)

    async def artist_desc(self, artist_id: int):
        # 歌手介绍
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/artist/introduction",
                                 {"id": artist_id},
                                 RequestOption(crypto=CryptoType.WEAPI))
        return await parse_response(response, APIArtistDescData)

    async def artist_list(self, category_code: int, initial: Optional[str], limit: int = 30, offset: int = 0):
        # 歌手分类
        # categoryCode 取值
        # 入驻歌手 5001
        # 华语男歌手 1001
        # 华语女歌手 1002
        # 华语组合/乐队 1003
        # 欧美男歌手 2001
        # 欧美女歌手 2002
        # 欧美组合/乐队 2003
        # 日本男歌手 6001
        # 日本女歌手 6002
        # 日本组合/乐队 6003
        # 韩国男歌手 7001
        # 韩国女歌手 7002
        # 韩国组合/乐队 7003
        # 其他男歌手 4001
        # 其他女歌手 4002
        # 其他组合/乐队 4003
        #
        # initial 取值 a-z/A-Z
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/artist/list",
                                 {
                                     "categoryCode": category_code,
                                     "initial": '' if not initial else initial.upper()[0],
                                     "offset": offset,
                                     "limit": limit,
                                     "total": True
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI))
        return await parse_response(response, APIArtistListData)

    async def artist_mv(self, artist_id: int, limit: int = 30, offset: int = 0):
        # 歌手相关mv
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/artist/mvs",
                                 {
                                     "artistId": artist_id,
                                     "offset": offset,
                                     "limit": limit,
                                     "total": True
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI))
        return await parse_response(response, APIArtistMVsData)

    async def artists(self, artist_id: int):
        # 歌手歌单
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/v1/artist/{artist_id}",
                                 {},
                                 RequestOption(crypto=CryptoType.WEAPI))
        return await parse_response(response, APIArtistSongsData)

    async def banner(self) -> APIBannersData:
        # 首页轮播图
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/api/v2/banner/get",
                                 {
                                     "clientType": "pc"
                                 },
                                 RequestOption(crypto=CryptoType.LINUX_API))
        return await parse_response(response, APIBannersData)

    async def mv_all(self, area: Optional[str] = None, type_: Optional[str] = None, order: Optional[str] = None,
                     limit: int = 30, offset: int = 0):
        # 全部MV
        # area: 地区,可选值为全部,内地,港台,欧美,日本,韩国,不填则为全部
        # type: 类型,可选值为全部,官方版,原生,现场版,网易出品,不填则为全部
        # order: 排序,可选值为上升最快,最热,最新,不填则为上升最快
        tags = json.dumps({"地区": area or "全部", "类型": type_ or "全部", "排序": order or "上升最快"})

        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://interface.music.163.com/weapi/mv/all",
                                 {
                                     "tags": tags,
                                     "offset": offset,
                                     "limit": limit,
                                     "total": True
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI))
        return await parse_response(response, APIMVAllData)

    async def mv_url(self, mv_id: int, resolution: Optional[int] = None):
        # mv 链接
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/song/enhance/play/mv/url",
                                 {
                                     "id": mv_id,
                                     "r": 1080 if not resolution else resolution
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI))
        return await parse_response(response, APIMVUrlData)

    async def mv_detail(self, mv_id: int):
        # MV 详情
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/mv/detail",
                                 {
                                     "id": mv_id,
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI))
        return await parse_response(response, APIMVDetailData)

    async def personalized(self, limit: int = 30) -> APIPersonalizedData:
        # 推荐歌单
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/personalized/playlist",
                                 {
                                     "limit": limit,
                                     "total": True,
                                     "n": 1000
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI))
        return await parse_response(response, APIPersonalizedData)

    async def personalized_newsong(self) -> APIPersonalizedNewSongData:
        # 推荐新歌
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/personalized/newsong",
                                 {
                                     "type": "recommend"
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI))
        return response
        # return await parse_response(response, APIPersonalizedNewSongData)

    async def personalized_mv(self):
        # 推荐mv
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/personalized/mv",
                                 {
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI))
        return await parse_response(response, APIPersonalizedMVData)

    async def comment_album(self, album_id: int, before_time: int = 0, limit: int = 20, offset: int = 0):
        # 专辑评论
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/v1/resource/comments/R_AL_3_{album_id}",
                                 {
                                     "rid": album_id,
                                     "limit": limit,
                                     "offset": offset,
                                     "beforeTime": before_time
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI))
        # return response
        return await parse_response(response, APIPersonalizedData)

    async def playlist_catlist(self):
        # 全部歌单分类
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/playlist/catalogue",
                                 {
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI))
        # return await parse_response(response, APIPlaylistCatListData)
        return response

    async def playlist_hot(self):
        # 热门歌单分类
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/playlist/hottags",
                                 {
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI))
        return response

    async def top_playlist_highquality(self, cat: str, limit: int = 30, lasttime: int = 0):
        # 精品歌单
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/playlist/highquality/list",
                                 {
                                     "cat": cat,
                                     "limit": limit,
                                     "lasttime": lasttime,
                                     "total": True
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI))
        return response

    async def top_playlist(self, cat: str, limit: int = 30, offset: int = 0):
        # 分类歌单
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/playlist/list",
                                 {
                                     "cat": cat,
                                     "limit": limit,
                                     "offset": offset,
                                     "order": "hot",
                                     "total": True
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI))
        return response

    async def user_detail(self, uid: int):
        # 用户详情
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/v1/user/detail/${uid}",
                                 {},
                                 RequestOption(crypto=CryptoType.WEAPI))
        return response

    async def song_detail(self, sids: Iterable[int]):
        # 歌曲详情
        cstr = "[" + ",".join([f'{{"id": {sid}}}' for sid in sids]) + "]"
        sid_str = "[" + ",".join([str(sid) for sid in sids]) + "]"

        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/v3/song/detail",
                                 {
                                     "c": cstr,
                                     "ids": sid_str
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI))
        return response
    async def song_url(self, sids: Iterable[int]):
        # 歌曲详情
        cstr = "[" + ",".join([f'{{"id": {sid}}}' for sid in sids]) + "]"
        sid_str = "[" + ",".join([str(sid) for sid in sids]) + "]"

        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/weapi/song/enhance/player/url",
                                 {
                                     "c": cstr,
                                     "ids": sid_str
                                 },
                                 RequestOption(crypto=CryptoType.WEAPI))
        return response



    async def lyric(self, sid: int):
        response = await request(self._http_session,
                                 HTTPMethod.POST,
                                 f"https://music.163.com/api/song/lyric?lv=-1&kv=-1&tv=-1",
                                 {
                                     "id":sid
                                 },
                                 RequestOption(crypto=CryptoType.LINUX_API))
        return response
