from enum import IntEnum
from typing import Dict, List, Any

from PyQt5.QtCore import QAbstractListModel, QModelIndex
from PyQt5.QtQuick import QQuickItem

from MusicPlayer.api.api import API
from MusicPlayer.api.data.personalized import APIPersonalizedItemData, APIPersonalizedData
from MusicPlayer.view_models.base import BaseViewModel


class _Dependency:
    def __init__(self, api: API):
        self.api = api

    # id: int
    # type: int
    # name: str
    # copywriter: str
    # pic_url: str
    # can_dislike: bool
    # track_number_update_time: int
    # play_count: float
    # track_count: int
    # high_quality: bool
    # alg: str
class _Roles(IntEnum):
    imageUrl = 0
    id = 1
    name = 2
    playCount = 3


class _BannerImageList(QAbstractListModel):
    _list: List[APIPersonalizedItemData]

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

    def set_data(self, data: APIPersonalizedData):
        self.beginResetModel()
        self._list.clear()
        self._list.extend(data.result)
        self.endResetModel()

    def data(self, index: QModelIndex, role: int) -> Any:
        if role == _Roles.imageUrl:
            return self._list[index.row()].pic_url
        elif role == _Roles.id:
            return self._list[index.row()].id
        elif role == _Roles.name:
            return self._list[index.row()].name
        elif role == _Roles.playCount:
            return self._list[index.row()].play_count

class RecommendationSongListsViewModel(BaseViewModel):
    _d: _Dependency

    def __init__(self, parent=None):
        super().__init__(_Dependency, parent)

    def componentComplete(self):

        super().componentComplete()

    async def load_recommendation_list(self):
        data = await self._d.api.personalized(9)
