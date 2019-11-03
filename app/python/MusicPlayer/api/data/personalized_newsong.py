from dataclasses import dataclass
from typing import List

from dataclasses_json import LetterCase, dataclass_json

from MusicPlayer.api.data.song_privilege import APISongPrivilegeData


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIPersonalizedNewSongResultSongAlbumData:
    id: int
    type: str
    name: str
    pic_url: str
    alias: List[str]


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIPersonalizedNewSongResultSongArtistData:
    id: int
    name: str
    alias: List[str]


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIPersonalizedNewSongResultSongData:
    id: int
    name: str
    alias: List[str]
    mvid: int
    artists: List[APIPersonalizedNewSongResultSongArtistData]
    album: APIPersonalizedNewSongResultSongAlbumData
    privilege: APISongPrivilegeData


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIPersonalizedNewSongResultData:
    id: int
    type: int
    name: str
    song: APIPersonalizedNewSongResultSongData


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIPersonalizedNewSongData:
    category: int
    result: List[APIPersonalizedNewSongResultData]
