from dataclasses import dataclass
from typing import List

from dataclasses_json import dataclass_json, LetterCase


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIPersonalizedMVResultArtistData:
    id: int
    name: str


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIPersonalizedMVResultData:
    id: int
    type: int
    name: str
    pic_url: str
    play_count: int
    artists: List[APIPersonalizedMVResultArtistData]
    artist_name: str
    artist_id: int


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIPersonalizedMVData:
    category: int
    result: List[APIPersonalizedMVResultData]
