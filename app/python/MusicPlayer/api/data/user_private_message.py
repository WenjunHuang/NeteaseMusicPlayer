from dataclasses import dataclass
from typing import List

from dataclasses_json import dataclass_json, LetterCase


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIUserPrivateMessageUserData:
    user_id: int
    nickname: str
    avatar_img_id: int
    user_type: int
    vip_type: int
    avatar_img_id_str: str
    background_img_id_str: str
    background_img_id: int
    birthday: int
    avatar_url: str
    background_url: str
    gender: int
    account_status: int
    city: int
    auth_status: int
    detail_description: str
    default_avatar: bool
    dj_status: int
    followed: bool
    description: str
    signature: str


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIUserPrivateMessageData:
    notice_account_flag: bool
    last_msg_time: int
    last_msg: str
    from_user: APIUserPrivateMessageUserData
    to_user: APIUserPrivateMessageUserData


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIUserPrivateMessagesData:
    more: bool
    new_msg_count: int
    msgs: List[APIUserPrivateMessageData]
