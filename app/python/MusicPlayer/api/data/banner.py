from dataclasses import dataclass
from typing import List

from dataclasses_json import dataclass_json, LetterCase


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIBannerData:
    image_url: str
    target_id: int
    target_type: int
    title_color: str
    type_title: str
    exclusive: bool
    encode_id: str
    scm: str


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIBannersData:
    banners: List[APIBannerData]
