from enum import IntEnum
from typing import Dict, Any, List

import pinject
import asyncio
from PyQt5.QtCore import QAbstractListModel, QModelIndex, pyqtProperty, pyqtSignal
from PyQt5.QtQuick import QQuickItem

from MusicPlayer.api.api import API
from MusicPlayer.api.data.banner import APIBannersData, APIBannerData
from MusicPlayer.common import with_logger
from MusicPlayer.object_graph import get_object_graph


class Roles(IntEnum):
    imageUrl = 0
    targetId = 1
    targetType = 2
    titleColor = 3
    typeTitle = 4
    encodeId = 5


class BannerImageList(QAbstractListModel):
    _list: List[APIBannerData]

    def __init__(self, parent=None):
        super().__init__(parent)
        self._list = []

    def roleNames(self) -> Dict[int, 'QByteArray']:
        roles = dict()

        for name, member in Roles.__members__.items():
            roles[member.value] = name.encode()

        return roles

    def rowCount(self, parent: QModelIndex) -> int:
        return len(self._list)

    def set_banners_data(self, data: APIBannersData):
        self.beginResetModel()
        self._list.clear()
        self._list.extend(data.banners)
        self.endResetModel()

    def data(self, index: QModelIndex, role: int) -> Any:
        if role == Roles.imageUrl:
            return self._list[index.row()].image_url
        elif role == Roles.encodeId:
            return self._list[index.row()].encode_id
        elif role == Roles.targetId:
            return self._list[index.row()].target_id
        elif role == Roles.targetType:
            return self._list[index.row()].target_type
        elif role == Roles.titleColor:
            return self._list[index.row()].title_color
        elif role == Roles.typeTitle:
            return self._list[index.row()].type_title


class BannerViewModelDependencies:
    def __init__(self, api: API):
        self.api = api


@with_logger
class BannerViewModel(QQuickItem):
    bannerCountChanged = pyqtSignal()

    def __init__(self, parent=None):
        super().__init__(parent)
        obj_graph: pinject.object_graph = get_object_graph()

        self._d = obj_graph.provide(BannerViewModelDependencies)
        self._banner_model = BannerImageList(self)

    def componentComplete(self):
        asyncio.create_task(self.load_banner_data())
        super().componentComplete()

    async def load_banner_data(self):
        banner_data = await self._d.api.banner()
        self._banner_model.set_banners_data(banner_data)
        self.bannerCountChanged.emit()

    @pyqtProperty(QAbstractListModel)
    def banners(self):
        return self._banner_model

    @pyqtProperty(int, notify=bannerCountChanged)
    def bannerCount(self):
        return self._banner_model.rowCount(QModelIndex())
