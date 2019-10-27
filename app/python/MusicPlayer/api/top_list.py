from dataclasses import dataclass, asdict
import aiohttp as http

from app.python.MusicPlayer.api.http import request, HTTPMethod, RequestOption, CryptoType


@dataclass
class TopMvQuery:
    area: str = ""
    limit: int = 30
    offset: int = 0
    total: bool = True


async def top_mv(query: TopMvQuery, session: http.ClientSession)->http.ClientResponse:
    return await request(session, HTTPMethod.POST,
                         "https://music.163.com/weapi/mv/toplist",
                         asdict(query),
                         RequestOption(crypto=CryptoType.WEAPI))
