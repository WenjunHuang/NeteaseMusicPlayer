import json
from typing import TypeVar, List, Union

import aiohttp
import logging

from MusicPlayer.api.error import APIError

T = TypeVar('T')


async def parse_response(response: aiohttp.ClientResponse, cls) -> Union[T, APIError]:
    if response.status == 200:
        return await deserialize_object(response, cls)
    else:
        return APIError(code=response.status)


def load(cls, value: str):
    return cls.from_json(value)


async def deserialize_object(response: aiohttp.ClientResponse, cls) -> Union[T, APIError]:
    try:
        jobj = await response.json(loads=json.loads)
        code = jobj['code']
        if code != 200:
            return APIError.from_dict(jobj)
        else:
            return cls.from_dict(jobj)
    except Exception as e:
        content_length = response.headers.get('Content-Length') or '(missing)'
        logging.warning(
            f"deserialize: invalid JSON found at '{response.url}' - status: {response.status}, length: {content_length}",
            e)
        raise
