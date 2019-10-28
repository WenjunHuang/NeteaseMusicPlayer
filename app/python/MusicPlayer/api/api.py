from typing import Union, Optional

import aiohttp
from typing_extensions import Literal
from Cryptodome.Hash import MD5

from MusicPlayer.api.http import request, HTTPMethod, RequestOption, CryptoType


class NeteaseMusicApi:
    def __init__(self, http_session: aiohttp.ClientSession):
        self._http_session = http_session

    async def dj_banner(self):
        return await request(self._http_session,
                             HTTPMethod.POST,
                             "https://music.163.com/weapi/djradio/banner/get",
                             {},
                             RequestOption(crypto=CryptoType.WEAPI, cookie={"os": "pc"}))

    async def dj_category_excludehot(self):
        return await request(self._http_session,
                             HTTPMethod.POST,
                             "https://music.163.com/weapi/djradio/category/excludehot",
                             {},
                             RequestOption(crypto=CryptoType.WEAPI))

    async def dj_category_recommend(self):
        return await request(self._http_session,
                             HTTPMethod.POST,
                             "https://music.163.com/weapi/djradio/home/category/recommend",
                             {},
                             RequestOption(crypto=CryptoType.WEAPI))

    async def dj_catelist(self):
        # 电台分类列表
        return await request(self._http_session,
                             HTTPMethod.POST,
                             "https://music.163.com/weapi/djradio/category/get",
                             {},
                             RequestOption(crypto=CryptoType.WEAPI))

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

    async def login_cellphone(self, password: str, phone: str, country_code: Optional[str] = None)->aiohttp.ClientResponse:
        password = MD5.new(password.encode('utf-8')).digest().hex()
        response =  await request(self._http_session,
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
        cookies= response.cookies
        print(cookies)
        return response
