import asyncio
import unittest

import aiohttp as http

from MusicPlayer.api.api import *


class TestUser(unittest.TestCase):
    def setUp(self) -> None:
        async def create_session():
            return http.ClientSession()
        self.loop = asyncio.get_event_loop()
        self.session = self.loop.run_until_complete(create_session())
        self.api = NeteaseMusicApi(self.session)

    def test_login_by_cellphone(self):
        result = self.loop.run_until_complete(self.api.login_cellphone("Rick198023","18027190235"))
        print(result)