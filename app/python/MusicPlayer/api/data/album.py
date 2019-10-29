from dataclasses import dataclass
from typing import List, Optional

from dataclasses_json import dataclass_json, LetterCase


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIAlbumDynamicData:
    on_sale: bool
    comment_count: int
    liked_count: int
    share_count: int
    is_sub: bool
    sub_time: int
    sub_count: int


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIArtistData:
    name: str
    id: int
    pic_id: int
    img1v1_id: str
    brief_desc: str
    pic_url: str
    img1v1_url: str
    album_size: int
    alias: List[str]
    trans: str
    music_size: int
    topic_person: int


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIAlbumData:
    name: str
    id: int
    type: str
    size: int
    pic_id: int
    blur_pic_url: str
    company_id: int
    pic: int
    pic_url: str
    publish_time: str
    description: str
    tags: str
    company: str
    brief_desc: str
    artists: List[APIArtistData]
    paid: bool
    on_sale: bool


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIAlbumNewestData:
    albums: List[APIAlbumData]


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIAlbumSubscriptionItemData:
    sub_time: int
    msg: List[str]
    alias: List[str]
    artists: List[APIArtistData]


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIAlbumSubscriptionListData:
    data: List[APIAlbumSubscriptionItemData]
    count: int
    has_more: bool
    paid_count: int


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APISongArtistData:
    id: int
    name: str
    alia: List[str]


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APISongAlbumData:
    id: int
    name: str
    pic_url: str
    pic: int
    alia: List[str]


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APISongQualityData:
    br: int
    fid: int
    size: int
    vd: float


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APISongPrivilegeData:
    id: int
    fee: int
    payed: int
    st: int
    pl: int
    dl: int
    sp: int
    cp: int
    subp: int
    cs: bool
    maxbr: int
    fl: int
    toast: bool
    flag: int
    pre_sell: bool


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APISongData:
    rt_urls: List[str]
    ar: List[APISongArtistData]
    al: APISongAlbumData
    st: int
    m: Optional[APISongQualityData]
    h: Optional[APISongQualityData]
    l: Optional[APISongQualityData]
    alia: List[str]
    pop: float
    rt: str
    name: str
    id: int
    privilege: APISongPrivilegeData


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIAlbumInfoData:
    songs: List[APISongData]
    album: APIAlbumData


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIArtistAlbumData:
    more:bool
    artist:APIArtistData
    hot_albums:List[APIAlbumData]