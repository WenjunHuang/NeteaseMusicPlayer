from dataclasses import dataclass, asdict

import aiohttp as http

from app.python.MusicPlayer.api.http import request, HTTPMethod, RequestOption, CryptoType


@dataclass
class DJProgramQuery:
    radioId: str
    limit: int = 30
    offset: int = 0
    asc: bool = True


async def dj_program(session: http.ClientSession, query: DJProgramQuery):
    return await request(session, HTTPMethod.POST,
                         "https://music.163.com/weapi/dj/program/byradio",
                         asdict(query),
                         RequestOption(crypto=CryptoType.WEAPI))
