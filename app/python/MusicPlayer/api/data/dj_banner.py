from dataclasses import dataclass
from typing import List, Optional

from dataclasses_json import dataclass_json, LetterCase


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIDJBannerData:
    target_id: int
    target_type: int
    pic: str
    url: str
    type_title: str
    exclusive: bool


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIDJBannersData:
    data: Optional[List[APIDJBannerData]]
