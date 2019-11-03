import asyncio
from enum import IntEnum
from typing import List, Dict, Any

from PyQt5.QtCore import QAbstractListModel, QModelIndex, pyqtProperty
from PyQt5.QtQuick import QQuickItem

from MusicPlayer.api.api import API
from MusicPlayer.api.data.personalized_newsong import APIPersonalizedNewSongResultData, APIPersonalizedNewSongData
from MusicPlayer.object_graph import get_object_graph
from MusicPlayer.view_models.base import BaseViewModel


class _Dependency:
    def __init__(self, api: API):
        self.api = api


class _Roles(IntEnum):
    imageUrl = 0
    id = 1
    name = 2
    nameAlias = 3
    isSq = 4
    mvId = 5
    artists = 6
    isCurrentSong = 7
    isCurrentSongPlaying = 8


class PersonalizedNewSongListModel(QAbstractListModel):
    _list: List[APIPersonalizedNewSongResultData]

    def __init__(self, parent=None):
        super().__init__(parent)
        self._list = []

    def roleNames(self) -> Dict[int, 'QByteArray']:
        roles = dict()

        for name, member in _Roles.__members__.items():
            roles[member.value] = name.encode()

        return roles

    def rowCount(self, parent: QModelIndex) -> int:
        return len(self._list)

    def reset_api_data(self, data: APIPersonalizedNewSongData):
        self.beginResetModel()
        self._list.clear()
        self._list.extend(data.result)
        self.endResetModel()

    def data(self, index: QModelIndex, role: int) -> Any:
        item = self._list[index.row()]

        if role == _Roles.imageUrl:
            return item.song.album.pic_url
        elif role == _Roles.name:
            return item.song.name
        elif role == _Roles.id:
            return item.song.id
        elif role == _Roles.nameAlias:
            return ','.join(item.song.alias)
        elif role == _Roles.artists:
            return ' / '.join([a.name for a in item.song.artists])
        elif role == _Roles.isCurrentSong:
            return False
        elif role == _Roles.isCurrentSongPlaying:
            return False
        elif role == _Roles.isSq:
            return item.song.privilege.maxbr == 999000  # 最大质量格式
        elif role == _Roles.mvId:
            return item.song.mvid


class PersonalizedNewSongViewModel(BaseViewModel):
    _d: _Dependency
    _list_model: PersonalizedNewSongListModel

    def __init__(self, parent=None):
        super().__init__(_Dependency, parent)
        self._list_model = PersonalizedNewSongListModel(self)

    def componentComplete(self):
        asyncio.create_task(self.load_data())
        super().componentComplete()

    async def load_data(self):
        data = await self._d.api.personalized_newsong()
        self._list_model.reset_api_data(data)

    @pyqtProperty(QAbstractListModel)
    def newSongListModel(self):
        return self._list_model
