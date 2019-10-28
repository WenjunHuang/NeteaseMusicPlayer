from dataclasses import dataclass, field
from typing import Optional

from dataclasses_json import dataclass_json, LetterCase


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIUserAccountData:
    id: int
    user_name: str
    type: int
    status: int
    create_time: int
    salt: str
    vip_type: int
    viptype_version: int


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIUserProfileData:
    user_id: int
    vip_type: int
    gender: 0
    avatar_img_id: int
    birthday: int
    city: int
    account_status: int
    nickname: str
    avatar_img_id_str: str
    background_img_id_str: str
    followed: bool
    description: str
    detail_description: str
    dj_status: int
    user_type: int
    default_avatar: bool
    avatar_url: str
    background_url: str
    avatar_img_id_str: str
    followeds: int
    follows: int
    event_count: int
    playlist_count: int
    playlist_be_subscribed_count: int


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIUserLoginData:
    login_type: int
    account: APIUserAccountData
    profile: APIUserProfileData

    cookies: Optional[str] = None
