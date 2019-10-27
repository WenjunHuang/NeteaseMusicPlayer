import asyncio
import unittest
import aiohttp as http

from app.python.MusicPlayer.api.dj_program import dj_program, DJProgramQuery
from app.python.MusicPlayer.api.top_list import top_mv, TopMvQuery


class TestTopList(unittest.TestCase):
    def setUp(self) -> None:
        self.loop = asyncio.get_event_loop()
        self.session = http.ClientSession()

    def tearDown(self) -> None:
        self.loop.stop()

    def test_top_list(self):
        result = self.loop.run_until_complete(dj_program(self.session, DJProgramQuery(radioId='336355127')))
        print(result)
        text = self.loop.run_until_complete(result.text())
        print(result.status)
        print(text)
