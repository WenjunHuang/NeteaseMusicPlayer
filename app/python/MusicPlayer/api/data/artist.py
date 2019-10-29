from dataclasses import dataclass
from typing import List

from dataclasses_json import dataclass_json, LetterCase

from MusicPlayer.api.data.album import APIArtistData


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIArtistTopicContentItemData:
    type: int
    id: int
    content: str


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIArtistTopicData:
    id: int
    add_time: int
    main_title: str
    title: str
    content: List[APIArtistTopicContentItemData]
    user_id: int
    cover: int
    head_pic: int
    share_content: str
    wx_title: str
    show_comment: bool
    status: int
    series_id: int
    pub_time: int
    read_count: int
    tags: List[str]
    start_text: str
    reward: bool
    summary: str
    category_id: int


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIArtistTopicCreatorData:
    user_id: int
    user_type: int
    nickname: str
    avatar_img_id: int
    avatar_url: str
    default_avatar: bool
    background_img_id: int
    background_url: str
    signature: str
    create_time: int
    user_name: str
    account_type: int
    short_user_name: str
    birthday: int
    authority: int
    gender: int
    account_status: int
    province: int
    city: int
    vip_type: int


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIArtistDescTopicData:
    topic: APIArtistTopicData
    creator: APIArtistTopicCreatorData
    share_count: int
    comment_count: int
    liked_count: int
    liked: bool
    reward_count: int
    rectangle_pic_url: str
    cover_url: str
    category_id: int
    category_name: str
    comment_thread_id: str
    main_title: str
    recmd_content: str
    share_content: str
    wx_title: str
    series_id: int
    read_count: int
    show_comment: bool
    show_related: bool
    summary: str
    recmd_title: str
    add_time: int
    reward: bool
    url: str
    title: str
    tags: List[str]
    id: int
    number: int


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIArtistDescIntroductionItemData:
    ti: str
    txt: str


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIArtistDescData:
    count: int
    brief_desc: str
    introduction: List[APIArtistDescIntroductionItemData]
    topic_data: List[APIArtistDescTopicData]


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIArtistListData:
    more: bool
    artists: List[APIArtistData]
