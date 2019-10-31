from dataclasses import dataclass
from typing import Optional

from dataclasses_json import dataclass_json


@dataclass_json
@dataclass
class APIHotCommentUserData:
    vip_type: int
    avatar_url: str
    nickname: str
    user_type: int
    user_id: int
    auth_status: int


@dataclass_json
@dataclass
class APIHotCommentPendantData:
    id: int
    image_url: str


@dataclass_json
@dataclass
class APIHotCommentData:
    user: APIHotCommentUserData
    status: int
    comment_id: int
    content: str
    time: int
    liked_count: int
    comment_location_type: int
    parent_comment_id: int
    prendant_data: Optional[APIHotCommentPendantData] = None


@dataclass_json
@dataclass
class APICommentAlbum:
    is_musician: bool
    user_id: int
    more_hot: bool
    total: int
    more: bool
