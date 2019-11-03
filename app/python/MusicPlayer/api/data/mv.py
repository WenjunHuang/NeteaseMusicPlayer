import json
from dataclasses import dataclass, field
from typing import List, Optional, Mapping
from dataclasses_json import dataclass_json, LetterCase, config
from MusicPlayer.api.data.album import APIArtistData
from MusicPlayer.convert import identity


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


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIMVDetailDataArtistData:
    id: int
    name: str




@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIMVDetailDataData:
    id: int
    name: str
    artist_id: int
    artist_name: str
    brief_desc: str
    cover: str
    cover_id: int
    play_count: int
    sub_count: int
    share_count: int
    like_count: int
    comment_count: int
    duration: int
    n_type: int
    publish_time: str
    brs: Mapping[str, str] = field(metadata=config(decoder=identity))
    artists: List[APIMVDetailDataArtistData]
    is_reward: bool
    comment_thread_id: str
    desc: Optional[str] = None


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIMVDetailData:
    loading_pic: str
    buffer_pic: str
    subed: bool
    data: APIMVDetailDataData


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIMVUrlDataData:
    id: int
    url: str
    r: int
    size: int
    md5: str
    code: int
    expi: int
    fee: int
    mv_fee: int
    st: int
    msg: str


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIMVUrlData:
    data: APIMVUrlDataData
