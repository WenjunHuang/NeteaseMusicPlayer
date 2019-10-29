import asyncio
import unittest

import aiohttp as http

from MusicPlayer.api.api import *


class TestTopList(unittest.TestCase):
    def setUp(self) -> None:
        async def create_session():
            return http.ClientSession()

        self.loop = asyncio.get_event_loop()
        self.session = self.loop.run_until_complete(create_session())
        self.api = NeteaseMusicApi(self.session)

    def tearDown(self) -> None:
        self.loop.run_until_complete(self.session.close())
        self.loop.stop()

    def test_dj_banner(self):
        result = self.loop.run_until_complete(self.api.dj_banner())
        print(result)

    def test_dj_category_excludehot(self):
        result = self.loop.run_until_complete(self.api.dj_category_excludehot())
        print(result)

    def test_dj_category_recommend(self):
        result = self.loop.run_until_complete(self.api.dj_category_recommend())
        print(result)

    def test_dj_catelist(self):
        result = self.loop.run_until_complete(self.api.dj_catelist())
        print(result)

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

    def test_album_detail_dynamic(self):
        result = self.loop.run_until_complete(self.api.album_detail_dynamic(32311))
        print(result)

    def test_album_newest(self):
        result = self.loop.run_until_complete(self.api.album_newest())
        print(result)

    def test_album_sublist(self):
        result = self.loop.run_until_complete(self.api.album_sublist(
            "MUSIC_U=32506ca1e2f682f81fb7fe6a0ebf3c74aa2cc9b11c17bf6e7c866ef355864c32efd7ce6cb42fd43d4b11618bec67fda741049cea1c6bb9b6; __remember_me=true; __csrf=2aaccbffd31aa62c906805f97dc5d834"))
        print(result)

    def test_album(self):
        result = self.loop.run_until_complete(self.api.album(32311))
        print(result)

    def test_artist_album(self):
        result = self.loop.run_until_complete(self.api.artist_album(6452))
        print(result)

    def test_artist_desc(self):
        result = self.loop.run_until_complete(self.api.artist_desc(6452))
        print(result)

    def test_artist_list(self):
        result = self.loop.run_until_complete(self.api.artist_list(1002, None, 30, 0))
        print(result)

    def test_artist_mv(self):
        result = self.loop.run_until_complete(self.api.artist_mv(9621))
        print(result)

    def test_artists(self):
        result = self.loop.run_until_complete(self.api.artists(9621))
        print(result)

    def test_banner(self):
        result = self.loop.run_until_complete(self.api.banner())
        print(result)

    def test_mv_all(self):
        result = self.loop.run_until_complete(self.api.mv_all(area="日本"))
        print(result)

    def test_mv_detail(self):
        result = self.loop.run_until_complete(self.api.mv_detail(5436712))
        print(result)

    def test_mv_url(self):
        result = self.loop.run_until_complete(self.api.mv_url(5436712))
        print(result)

    def test_personalized(self):
        result = self.loop.run_until_complete(self.api.personalized(4))
        print(result)
        text = self.loop.run_until_complete(result.text())
        print(result.status)
        print(text)
