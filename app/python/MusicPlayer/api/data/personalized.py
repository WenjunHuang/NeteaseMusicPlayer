from dataclasses import dataclass
from typing import List

from dataclasses_json import dataclass_json, LetterCase


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIPersonalizedItemData:
    id: int
    type: int
    name: str
    copywriter: str
    pic_url: str
    can_dislike: bool
    track_number_update_time: int
    play_count: float
    track_count: int
    high_quality: bool
    alg: str


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIPersonalizedData:
    has_taste: bool
    category: int
    result: List[APIPersonalizedItemData]
