#include <QtCore>
#include <cryptopp/aes.h>
#include <cryptopp/base64.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/randpool.h>
#include <cryptopp/rsa.h>
#include <iostream>
#include <string>

QByteArray aesEncryptCBC(const QByteArray& buffer, const QByteArray& key,
                         const QByteArray& iv) {
    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryptor(
        reinterpret_cast<const byte*>(key.data()),
        CryptoPP::AES::DEFAULT_KEYLENGTH,
        reinterpret_cast<const byte*>(iv.data()));

    std::string ciphertext;
    CryptoPP::StreamTransformationFilter stfEnc(
        encryptor, new CryptoPP::StringSink(ciphertext));
    stfEnc.Put(reinterpret_cast<const unsigned char*>(buffer.data()),
               buffer.length());
    stfEnc.MessageEnd();

    return QByteArray(ciphertext.c_str(), ciphertext.size());
}

QByteArray aseEncryptECB(const QByteArray& buffer, const QByteArray& key) {
    CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption encryptor(
        reinterpret_cast<const byte*>(key.data()),
        CryptoPP::AES::DEFAULT_KEYLENGTH);

    std::string ciphertext;
    CryptoPP::StreamTransformationFilter stfEnc(
        encryptor, new CryptoPP::StringSink(ciphertext));
    stfEnc.Put(reinterpret_cast<const unsigned char*>(buffer.data()),
               buffer.length());
    stfEnc.MessageEnd();

    return QByteArray(ciphertext.c_str(), ciphertext.size());
}

QByteArray padForEncryption(const QByteArray& buffer, size_t targetLength) {
    auto paddingLength = targetLength - buffer.length();
    QByteArray result;
    result.append(buffer);
    result.append(paddingLength, 0);

    std::reverse(result.begin(), result.end());
    return result;
}

QByteArray rsaEncrypt(const QByteArray& buffer, const QByteArray& key) {
    CryptoPP::StringSource ss(reinterpret_cast<const byte*>(key.data()),
                              key.length(), true,
                              new CryptoPP::Base64Decoder());
    CryptoPP::RSA::PublicKey pk;
    pk.Load(ss);
    QByteArray rawBuffer =
        padForEncryption(buffer, pk.GetModulus().ByteCount());
    CryptoPP::Integer m(
        reinterpret_cast<const unsigned char*>(rawBuffer.data()),
        rawBuffer.length());
    CryptoPP::Integer c = pk.ApplyFunction(m);
    QByteArray result;
    for (int i = c.ByteCount() - 1; i >= 0; i--)
        result.append(c.GetByte(i));
    return result;
}