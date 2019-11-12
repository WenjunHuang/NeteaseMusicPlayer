#include <QtCore>
#include <QUrlQuery>
#include <cryptopp/aes.h>
#include <cryptopp/base64.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/rsa.h>
#include <string>

inline const QByteArray kIV("0102030405060708");
inline const QByteArray kPresetKey("0CoJUm6Qyw8W8jud");
inline const QByteArray kLinuxapiKey("rFgB&h#%2?^eDg:Q");
inline const QByteArray
  kBase62("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
inline const QByteArray kPublicKey(
  "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDgtQn2JZ34ZC28NWYpAUd98iZ37BUrX/"
  "aKzmFbt7clFSs6sXqHauqKWqdtLkF2KexO40H1YTX8z2lSgBBOAxLsvaklV8k4cBFK9snQXE9/"
  "DDaFt6Rr7iVZMldczhC0JNgTz+"
  "SHXT6CBHuX3e9SdB1Ua44oncaTWz7OBGLbCiK45wIDAQAB");
inline QByteArray kEapiKey("e82ckenh8dichen8");

#ifdef Q_OS_MACOS
#define byte CryptoPP::byte
#endif

QByteArray aesEncryptCBC(const QByteArray &buffer, const QByteArray &key,
                         const QByteArray &iv) {
  CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryptor(
    reinterpret_cast<const byte *>(key.data()),
    CryptoPP::AES::DEFAULT_KEYLENGTH,
    reinterpret_cast<const byte *>(iv.data()));

  std::string ciphertext;
  CryptoPP::StreamTransformationFilter stfEnc(
    encryptor, new CryptoPP::StringSink(ciphertext));
  stfEnc.Put(reinterpret_cast<const unsigned char *>(buffer.data()),
             buffer.length());
  stfEnc.MessageEnd();

  return QByteArray(ciphertext.c_str(), ciphertext.size());
}

QByteArray aseEncryptECB(const QByteArray &buffer, const QByteArray &key) {
  CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption encryptor(
    reinterpret_cast<const byte *>(key.data()),
    CryptoPP::AES::DEFAULT_KEYLENGTH);

  std::string ciphertext;
  CryptoPP::StreamTransformationFilter stfEnc(
    encryptor, new CryptoPP::StringSink(ciphertext));
  stfEnc.Put(reinterpret_cast<const unsigned char *>(buffer.data()),
             buffer.length());
  stfEnc.MessageEnd();

  return QByteArray(ciphertext.c_str(), ciphertext.size());
}

QByteArray padForEncryption(const QByteArray &buffer, size_t targetLength) {
  auto paddingLength = targetLength - buffer.length();
  QByteArray result;
  result.append(buffer);
  result.append(paddingLength, 0);

  std::reverse(result.begin(), result.end());
  return result;
}

QByteArray rsaEncrypt(const QByteArray &buffer, const QByteArray &key) {
  CryptoPP::StringSource ss(reinterpret_cast<const byte *>(key.data()),
                            key.length(), true,
                            new CryptoPP::Base64Decoder());
  CryptoPP::RSA::PublicKey pk;
  pk.Load(ss);
  QByteArray rawBuffer =
    padForEncryption(buffer, pk.GetModulus().ByteCount());
  CryptoPP::Integer m(
    reinterpret_cast<const unsigned char *>(rawBuffer.data()),
    rawBuffer.length());
  CryptoPP::Integer c = pk.ApplyFunction(m);
  QByteArray result;
  for (int i = c.ByteCount() - 1; i >= 0; i--)
    result.append(c.GetByte(i));
  return result;
}

QByteArray weapi(const QVariantHash &data) {
  QByteArray secretKey{16, 0};
  for (auto &i: secretKey) {
    i = kBase62[QRandomGenerator::global()->generate() % 62];
  }
  QByteArray text{QJsonDocument(QJsonObject::fromVariantHash(data)).toJson(QJsonDocument::Compact)};

  // 需要使用两次aes加密
  auto first = aesEncryptCBC(text, kPresetKey, kIV).toBase64();
  auto params = aesEncryptCBC(first, secretKey, kIV).toBase64();
  auto encSecKey = rsaEncrypt(secretKey, kPublicKey).toHex();

  QUrlQuery result;
  result.addQueryItem("params", params);
  result.addQueryItem("encSecKey", encSecKey);
  auto r = result.toString(QUrl::FullyEncoded).toUtf8();
  r.replace(QChar('+'), "%2B"); // Qt的bug:不会转意+字符
  return r;
}

QByteArray linuxApi(const QVariantHash &data) {
  QByteArray text{QJsonDocument(QJsonObject::fromVariantHash(data)).toJson(QJsonDocument::Compact)};
  auto eparams = aseEncryptECB(text, kLinuxapiKey).toHex().toUpper();
  QUrlQuery result;
  result.addQueryItem("eparams", eparams);
  auto r = result.toString(QUrl::FullyEncoded).toUtf8();
  r.replace(QChar('+'), "%2B"); // Qt的bug:不会转意+字符
  return r;
}