import pinject
from PyQt5.QtQuick import QQuickItem

from MusicPlayer.object_graph import get_object_graph


class BaseViewModel(QQuickItem):
    def __init__(self, dep_cls, parent=None):
        super().__init__(parent)
        obj_graph: pinject.object_graph = get_object_graph()
        self._d = obj_graph.provide(dep_cls)
