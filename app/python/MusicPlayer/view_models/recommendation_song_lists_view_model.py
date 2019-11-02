from dataclasses import dataclass, field
from datetime import datetime
from enum import IntEnum
from typing import Dict, List, Any, Union
import asyncio
from PyQt5.QtCore import QAbstractListModel, QModelIndex, Q_ENUM, pyqtProperty

from MusicPlayer.api.api import API
from MusicPlayer.api.data.personalized import APIPersonalizedItemData, APIPersonalizedData
from MusicPlayer.datetime_util import local_now_with_timezone
from MusicPlayer.view_models.base import BaseViewModel


class _Dependency:
    def __init__(self, api: API):
        self.api = api


@dataclass
class _EveryDayRecommendation:
    name: str = field(init=False, default="每日歌曲推荐")
    tips: str = field(init=False, default="根据您的音乐口味生成每日更新")
    today: datetime = field(init=False, default_factory=local_now_with_timezone)


class _ItemKind(IntEnum):
    Normal = 0
    EveryDay = 1


class _Roles(IntEnum):
    imageUrl = 0
    id = 1
    name = 2
    playCount = 3
    tips = 4
    today = 5
    kind = 6


_ModelItem = Union[_EveryDayRecommendation, APIPersonalizedItemData]


class _RecommendationSongsListModel(QAbstractListModel):
    _list: List[_ModelItem]

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

    def reset_api_data(self, data: APIPersonalizedData):
        self.beginResetModel()
        self._list.clear()
        # self._list.append(_EveryDayRecommendation())
        self._list.extend(data.result)
        self.endResetModel()

    def data(self, index: QModelIndex, role: int) -> Any:
        item = self._list[index.row()]
        if type(item) == APIPersonalizedItemData:
            if role == _Roles.imageUrl:
                return item.pic_url
            elif role == _Roles.id:
                return item.id
            elif role == _Roles.name:
                return item.name
            elif role == _Roles.playCount:
                if item.play_count > 10000:
                    return f"{int(item.play_count/10000)}万"
                else:
                    return f"{int(item.play_count)}"
            elif role == _Roles.kind:
                return _ItemKind.Normal
            elif role == _Roles.tips:
                return None
            elif role == _Roles.today:
                return None

        if type(item) == _EveryDayRecommendation:
            if role == _Roles.imageUrl:
                return None
            elif role == _Roles.id:
                return -1
            elif role == _Roles.name:
                return item.name
            elif role == _Roles.playCount:
                return None
            elif role == _Roles.kind:
                return _ItemKind.EveryDay
            elif role == _Roles.tips:
                return item.tips
            elif role == _Roles.today:
                return item.today.day


class RecommendationSongListsViewModel(BaseViewModel):
    _d: _Dependency

    Q_ENUM(_ItemKind)

    def __init__(self, parent=None):
        super().__init__(_Dependency, parent)
        self._list_model = _RecommendationSongsListModel(self)

    def componentComplete(self):
        asyncio.create_task(self.load_recommendation_list())
        super().componentComplete()

    async def load_recommendation_list(self):
        data = await self._d.api.personalized(10)
        self._list_model.reset_api_data(data)

    @pyqtProperty(QAbstractListModel)
    def songLists(self):
        return self._list_model
