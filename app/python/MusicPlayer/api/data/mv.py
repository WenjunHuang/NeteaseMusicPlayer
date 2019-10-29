from dataclasses import dataclass
from typing import List, Optional
from dataclasses_json import dataclass_json, LetterCase
from MusicPlayer.api.data.album import APIArtistData


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIArtistMVData:
    id: int
    name: str
    status: int
    artist_name: str
    imgurl: str
    imgurl16v9: str
    artist: APIArtistData
    duration: int
    play_count: int
    publish_time: int
    subed: bool


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIArtistMVsData:
    mvs: List[APIArtistMVData]
    time: int
    has_more: bool


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIMVArtistData:
    id: int
    name: str
    alias: List[str]
    trans_names: List[str]


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIMVData:
    id: int
    cover: str
    name: str
    play_count: int
    brief_desc: str
    artist_name: str
    artist_id: int
    duration: int
    mark: int
    subed: bool
    artists: List[APIMVArtistData]
    desc: Optional[str] = None


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIMVAllData:
    has_more: bool
    count: int
    data: List[APIMVData]
