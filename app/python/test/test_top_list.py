import asyncio
import unittest

import aiohttp as http

from MusicPlayer.api.api import *


class TestTopList(unittest.TestCase):
    def setUp(self) -> None:
        self.loop = asyncio.get_event_loop()
        self.session = http.ClientSession()
        self.api = NeteaseMusicApi(self.session)

    def tearDown(self) -> None:
        self.loop.stop()

    def test_dj_banner(self):
        result = self.loop.run_until_complete(self.api.dj_banner())
        print(result)
        text = self.loop.run_until_complete(result.text())
        print(result.status)
        print(text)

    def test_dj_category_excludehot(self):
        result = self.loop.run_until_complete(self.api.dj_category_excludehot())
        print(result)
        text = self.loop.run_until_complete(result.text())
        print(result.status)
        print(text)

    def test_dj_category_recommend(self):
        result = self.loop.run_until_complete(self.api.dj_category_recommend())
        print(result)
        text = self.loop.run_until_complete(result.text())
        print(result.status)
        print(text)

    def test_dj_catelist(self):
        result = self.loop.run_until_complete(self.api.dj_catelist())
        print(result)
        text = self.loop.run_until_complete(result.text())
        print(result.status)
        print(text)

    def test_dj_detail(self):
        result = self.loop.run_until_complete(self.api.dj_detail('793094397'))
        print(result)
        text = self.loop.run_until_complete(result.text())
        print(result.status)
        print(text)

    def test_dj_hot(self):
        result = self.loop.run_until_complete(self.api.dj_hot(30, 0))
        print(result)
        text = self.loop.run_until_complete(result.text())
        print(result.status)
        print(text)

    def test_dj_paygift(self):
        result = self.loop.run_until_complete(self.api.dj_paygift(30, 0))
        print(result)
        text = self.loop.run_until_complete(result.text())
        print(result.status)
        print(text)

    def test_dj_program_detail(self):
        result = self.loop.run_until_complete(self.api.dj_program_detail("1398701806"))
        print(result)
        text = self.loop.run_until_complete(result.text())
        print(result.status)
        print(text)

    def test_dj_program_toplist(self):
        result = self.loop.run_until_complete(self.api.dj_program_toplist(30, 0))
        print(result)
        text = self.loop.run_until_complete(result.text())
        print(result.status)
        print(text)

    def test_dj_program(self):
        result = self.loop.run_until_complete(self.api.dj_program("336355127", 30, 0, False))
        print(result)
        text = self.loop.run_until_complete(result.text())
        print(result.status)
        print(text)

    def test_dj_radio_hot(self):
        result = self.loop.run_until_complete(self.api.dj_radio_hot(3, 30, 0))
        print(result)
        text = self.loop.run_until_complete(result.text())
        print(result.status)
        print(text)

    def test_dj_recommend_type(self):
        result = self.loop.run_until_complete(self.api.dj_recommend_type(1))
        print(result)
        text = self.loop.run_until_complete(result.text())
        print(result.status)
        print(text)

    def test_dj_recommend(self):
        result = self.loop.run_until_complete(self.api.dj_recommend())
        print(result)
        text = self.loop.run_until_complete(result.text())
        print(result.status)
        print(text)

    def test_dj_today_perfered(self):
        result = self.loop.run_until_complete(self.api.dj_today_perfered(1))
        print(result)
        text = self.loop.run_until_complete(result.text())
        print(result.status)
        print(text)

    def test_dj_toplist(self):
        result = self.loop.run_until_complete(self.api.dj_toplist(30, 0, 1))
        print(result)
        text = self.loop.run_until_complete(result.text())
        print(result.status)
        print(text)


