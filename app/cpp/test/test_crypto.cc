#define CATCH_CONFIG_MAIN
#include <QtCore>
#include "./catch2/catch.hpp"
#include "../MusicPlayer/api/crypto.h"

TEST_CASE("Factorials are computed", "[crypto]") {
    QByteArray data{"{\"radioId\":\"336355127\",\"limit\":30,\"offset\":0,"
                    "\"asc\":false,\"csrf_token\":\"\"}"};
    QByteArray key{"0CoJUm6Qyw8W8jud"};
    QByteArray iv{"0102030405060708"};
    QString result(aesEncryptCBC(data,key,iv).toBase64());

    qDebug() << result;
}

TEST_CASE("RSA","[RSA]") {
    QByteArray data{"{\"radioId\":\"336355127\",\"limit\":30,\"offset\":0,"
                    "\"asc\":false,\"csrf_token\":\"\"}"};
    QByteArray key{"0CoJUm6Qyw8W8jud"};
    QByteArray iv{"0102030405060708"};

    //QString result(rsaEncrypt(data,publicKey).toHex());

    //qDebug() << result;
}