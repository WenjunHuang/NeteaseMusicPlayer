import base64
import unittest

from app.python.MusicPlayer.api.crypto import Crypto, public_key


class TestCrypto(unittest.TestCase):
    def test_aes_encrypt(self):
        data = b'{"radioId":"336355127","limit":30,"offset":0,"asc":false,"csrf_token":""}'
        key = b'0CoJUm6Qyw8W8jud'
        iv = b'0102030405060708'
        print(base64.b64encode(Crypto.aes_encrypt(data, key, iv)))
        print(Crypto.rsa_encrypt(key, public_key).hex())
