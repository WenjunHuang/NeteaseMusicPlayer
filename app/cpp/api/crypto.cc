#include <QtCore>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/rsa.h>
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

QByteArray rsaEncrypt(const QByteArray& buffer, const QByteArray& key) {
    CryptoPP::StringSource ss(key.data(), true);
    CryptoPP::RSA::PublicKey pk;
    pk.Load(ss);
    pk.
}
