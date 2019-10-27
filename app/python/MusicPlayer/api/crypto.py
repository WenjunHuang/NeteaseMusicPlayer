import base64
import json
import os
from dataclasses import dataclass
from typing import Mapping

from Crypto.Cipher import AES
from Crypto.Cipher.AES import MODE_CBC
from Crypto.PublicKey import RSA
from Crypto.Util.Padding import pad
from Crypto.Util.number import bytes_to_long, long_to_bytes

iv = b'0102030405060708'
preset_key = b'0CoJUm6Qyw8W8jud'
base62 = b'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'
public_key = b'-----BEGIN PUBLIC KEY-----\nMIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDgtQn2JZ34ZC28NWYpAUd98iZ37BUrX/aKzmFbt7clFSs6sXqHauqKWqdtLkF2KexO40H1YTX8z2lSgBBOAxLsvaklV8k4cBFK9snQXE9/DDaFt6Rr7iVZMldczhC0JNgTz+SHXT6CBHuX3e9SdB1Ua44oncaTWz7OBGLbCiK45wIDAQAB\n-----END PUBLIC KEY-----'
eapi_key = b'e82ckenh8dichen8'


# BS = 16
# def pad(data):
#     padding = BS - len(data) % BS
#     return data + padding * chr(padding)


@dataclass
class WEAPIResult:
    params: str
    encSecKey: str


def pad_for_encryption(message: bytes, target_length: int):
    message = message[::-1]
    msglength = len(message)

    padding = b''
    padding_length = target_length - msglength - 3

    for i in range(padding_length):
        padding += b'\x00'

    return b''.join([b'\x00\x00', padding, b'\x00', message])


class Crypto:
    @classmethod
    def aes_encrypt(cls, data: bytes, key: bytes, iv: bytes) -> bytes:
        cipher = AES.new(key, MODE_CBC, iv)
        return cipher.encrypt(pad(data, 16))

    @classmethod
    def rsa_encrypt(cls, data: bytes, key: bytes) -> bytes:
        data = data[::-1]
        rsa_key = RSA.import_key(key)
        data = pad_for_encryption(data, rsa_key.size_in_bytes())
        return long_to_bytes(rsa_key._encrypt(bytes_to_long(data)))

    @classmethod
    def weapi(cls, data: Mapping[str, str]):
        secret_key = ''.join([chr(base62[n % 62]) for n in os.urandom(16)])
        text = json.dumps(data)

        return WEAPIResult(
            params=base64.b64encode(Crypto.aes_encrypt(text.encode('utf-8'), secret_key.encode('utf-8'), iv)).decode(
                'utf-8'),
            encSecKey=Crypto.rsa_encrypt(secret_key.encode('utf-8'), public_key).hex())
