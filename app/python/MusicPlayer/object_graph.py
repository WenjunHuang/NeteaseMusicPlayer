from typing import Optional

import pinject

object_graph = None


def set_object_graph(obj):
    global object_graph
    object_graph = obj


def get_object_graph():
    global object_graph
    return object_graph
