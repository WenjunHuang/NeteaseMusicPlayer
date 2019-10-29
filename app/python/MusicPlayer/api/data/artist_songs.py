from dataclasses import dataclass
from typing import List

from dataclasses_json import dataclass_json, LetterCase

from MusicPlayer.api.data.album import APIArtistData, APISongData


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIArtistSongsData:
    artist: APIArtistData
    hot_songs: List[APISongData]
    more: bool
