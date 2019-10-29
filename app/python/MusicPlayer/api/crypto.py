import base64
import json
import os
from dataclasses import dataclass
from typing import Mapping, Any, Union, Optional

from Cryptodome.Cipher import AES
from Cryptodome.Cipher.AES import MODE_CBC, MODE_ECB
from Cryptodome.PublicKey import RSA
from Cryptodome.Hash import MD5
from Cryptodome.Util.Padding import pad
from Cryptodome.Util.number import bytes_to_long, long_to_bytes

iv = b'0102030405060708'
preset_key = b'0CoJUm6Qyw8W8jud'
base62 = b'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'
public_key = b'-----BEGIN PUBLIC KEY-----\nMIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDgtQn2JZ34ZC28NWYpAUd98iZ37BUrX/aKzmFbt7clFSs6sXqHauqKWqdtLkF2KexO40H1YTX8z2lSgBBOAxLsvaklV8k4cBFK9snQXE9/DDaFt6Rr7iVZMldczhC0JNgTz+SHXT6CBHuX3e9SdB1Ua44oncaTWz7OBGLbCiK45wIDAQAB\n-----END PUBLIC KEY-----'
eapi_key = b'e82ckenh8dichen8'
linux_api_key = b'rFgB&h#%2?^eDg:Q'


# BS = 16
# def pad(data):
#     padding = BS - len(data) % BS
#     return data + padding * chr(padding)


@dataclass
class WEAPIResult:
    params: str
    encSecKey: str


@dataclass
class LinuxAPIResult:
    eparams: str


@dataclass
class EAPIResult:
    params: str


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
    def aes_encrypt(cls, data: bytes, key: bytes, iv: bytes, mode=MODE_CBC) -> bytes:
        if mode == MODE_CBC:
            cipher = AES.new(key, mode, iv)
        if mode == MODE_ECB:
            cipher = AES.new(key, mode)
        return cipher.encrypt(pad(data, 16))

    @classmethod
    def rsa_encrypt(cls, data: bytes, key: bytes) -> bytes:
        rsa_key = RSA.import_key(key)
        return long_to_bytes(rsa_key._encrypt(bytes_to_long(pad_for_encryption(data, rsa_key.size_in_bytes()))))

    @classmethod
    def weapi(cls, data: Mapping[str, str]):
        global preset_key
        secret_key = ''.join([chr(base62[n % 62]) for n in os.urandom(16)]).encode('utf-8')
        text = json.dumps(data)

        result = WEAPIResult(
            # 需要两次使用aes加密
            params=base64.b64encode(
                Crypto.aes_encrypt(base64.b64encode(Crypto.aes_encrypt(text.encode('utf-8'), preset_key, iv)),
                                   secret_key, iv)).decode('utf-8'),
            encSecKey=Crypto.rsa_encrypt(secret_key, public_key).hex())
        print(result)
        return result

    @classmethod
    def linux_api(cls, data: Mapping[str, Any]):
        text = json.dumps(data)
        return LinuxAPIResult(
            eparams=Crypto.aes_encrypt(text.encode('utf-8'), linux_api_key, None, MODE_ECB).hex().upper()
        )

    @classmethod
    def eapi(cls, url: str, data: Union[str, Mapping[str, Any]]):
        if type(data) == str:
            text = data
        else:
            text = json.dumps(data)

        message = f"nobody{url}use{text}md5forencrypt"
        digest = MD5.new(message.encode('utf-8')).digest().hex()
        data = f"{url}-36cd479b6b5-{text}-36cd479b6b5-{digest}"

        return EAPIResult(
            params=Crypto.aes_encrypt(data.encode('utf-8'), eapi_key, '', MODE_ECB).hex().upper()
        )
