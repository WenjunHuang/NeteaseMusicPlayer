import asyncio
import os
import sqlite3
import sys

import aiohttp
import aiosqlite
import pinject
import rx
from PyQt5.QtGui import QGuiApplication
from PyQt5.QtQml import QQmlApplicationEngine
from aiosqlite import Connection
from asyncqt import QEventLoop

from MusicPlayer.api.api import API


class BasicBindingSpec(pinject.BindingSpec):
    def provide_app(self):
        sys_argv = sys.argv
        sys_argv += ['--style', './ui/MusicPlayer']
        return QGuiApplication(sys.argv)

    def provide_qml_engine(self, app):
        # must dependent on app
        return QQmlApplicationEngine()

    def provide_event_loop(self, app):
        loop = QEventLoop(app)
        asyncio.set_event_loop(loop)
        asyncio.events._set_running_loop(loop)
        return loop


class DatabaseBindingSpec(pinject.BindingSpec):
    def provide_database(self, config_dir):
        db_file = 'music.db'
        db_file_path = os.path.join(config_dir, db_file)
        db = asyncio.get_event_loop().run_until_complete(aiosqlite.connect(db_file_path))
        db.row_factory = sqlite3.Row
        return db


class HttpApiBindingSpec(pinject.BindingSpec):
    def provide_api(self, http_session):
        return API(http_session)

    def provide_http_session(self):
        # return event_loop.run_until_complete(aiohttp.ClientSession(json_serialize=json_generator))
        return aiohttp.ClientSession()

    def dependencies(self):
        return [BasicBindingSpec()]


class EventStreamBindingSpec(pinject.BindingSpec):
    def provide_error_subject(self):
        return rx.subject.Subject()

    def provide_accounts_updated_subject(self):
        return rx.subject.Subject()

    def provide_authenticated_subject(self):
        return rx.subject.Subject()

    def provide_selected_state(self):
        return rx.subject.BehaviorSubject(None)


class AppBindingSpec(pinject.BindingSpec):
    '''wrap all binding specs'''

    def dependencies(self):
        return [HttpApiBindingSpec(), DatabaseBindingSpec(), BasicBindingSpec(), EventStreamBindingSpec()]
