import re
from dataclasses import dataclass, field, asdict
from enum import IntEnum, Enum
from random import randrange
from typing import Optional, Mapping, Any
from urllib.parse import quote_plus

import aiohttp as http

from app.python.MusicPlayer.api.crypto import Crypto

kUserAgentList = [
    'Mozilla/5.0 (iPhone; CPU iPhone OS 9_1 like Mac OS X) AppleWebKit/601.1.46 (KHTML, like Gecko) Version/9.0 Mobile/13B143 Safari/601.1',
    'Mozilla/5.0 (iPhone; CPU iPhone OS 9_1 like Mac OS X) AppleWebKit/601.1.46 (KHTML, like Gecko) Version/9.0 Mobile/13B143 Safari/601.1',
    'Mozilla/5.0 (Linux; Android 5.0; SM-G900P Build/LRX21T) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Mobile Safari/537.36',
    'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Mobile Safari/537.36',
    'Mozilla/5.0 (Linux; Android 5.1.1; Nexus 6 Build/LYZ28E) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Mobile Safari/537.36',
    'Mozilla/5.0 (iPhone; CPU iPhone OS 10_3_2 like Mac OS X) AppleWebKit/603.2.4 (KHTML, like Gecko) Mobile/14F89;GameHelper',
    'Mozilla/5.0 (iPhone; CPU iPhone OS 10_0 like Mac OS X) AppleWebKit/602.1.38 (KHTML, like Gecko) Version/10.0 Mobile/14A300 Safari/602.1',
    'Mozilla/5.0 (iPad; CPU OS 10_0 like Mac OS X) AppleWebKit/602.1.38 (KHTML, like Gecko) Version/10.0 Mobile/14A300 Safari/602.1',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:46.0) Gecko/20100101 Firefox/46.0',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Safari/537.36',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_5) AppleWebKit/603.2.4 (KHTML, like Gecko) Version/10.1.1 Safari/603.2.4',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:46.0) Gecko/20100101 Firefox/46.0',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.135 Safari/537.36 Edge/13.10586'
]


class UserAgentType(IntEnum):
    Mobile = 0
    PC = 1


class HTTPMethod(Enum):
    GET = "GET"
    POST = "POST"
    PUT = "PUT"
    HEAD = "HEAD"


class CryptoType(IntEnum):
    WEAPI = 0
    LINUX_API = 1
    EAPI = 2


@dataclass
class RequestOption:
    crypto: CryptoType
    cookie: Mapping[str, str] = field(default_factory=dict)
    ua: Optional[UserAgentType] = None


def choose_user_agent(ua: Optional[UserAgentType]):
    global kUserAgentList
    if not ua:
        index = randrange(len(kUserAgentList))
    elif ua == UserAgentType.Mobile:
        index = randrange(8)
    else:
        index = randrange(8, len(kUserAgentList))
    return kUserAgentList[index]


async def request(session: http.ClientSession, method: HTTPMethod, url: str, data: Mapping[str, Any],
                  options: RequestOption):
    headers = {'User-Agent': choose_user_agent(options.ua)}
    if method == HTTPMethod.POST:
        headers['Content-Type'] = 'application/x-www-form-urlencoded'
    if url.find('music.163.com') != -1:
        headers['Referer'] = 'https://music.163.com'

    headers['Cookie'] = '; '.join([f"{quote_plus(key)}={quote_plus(value)}" for key, value in options.cookie.items()])

    if options.crypto == CryptoType.WEAPI:
        regex = re.compile(r"_csrf=([^(;|$)]+)")
        csrf_token = regex.findall(headers.get('Cookie', ''))
        if csrf_token:
            data['csrf_token'] = csrf_token[1]
        else:
            data['csrf_token'] = ''
        data = Crypto.weapi(data)

    # request = http.ClientRequest(method=method.value,
    #                    url = url,
    #                    headers=headers,
    #                    data=asdict(data))
    # return await request.send(session)
    return await session.request(method.value,
                                 url,
                                 headers=headers,
                                 data=asdict(data))
