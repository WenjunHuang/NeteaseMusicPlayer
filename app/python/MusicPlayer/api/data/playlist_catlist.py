from dataclasses import field, dataclass
from typing import List,Mapping

from dataclasses_json import dataclass_json, LetterCase, config

from MusicPlayer.convert import identity


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIPlaylistCatListItemData:
    name: str
    resource_count: int
    img_id: int
    type: int
    category: int
    resource_type: int
    hot: bool
    activity: bool


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIPlaylistCatListData:
    all: APIPlaylistCatListItemData
    sub: List[APIPlaylistCatListItemData]
    categories: Mapping[str, str] = field(metadata=config(decoder=identity))
