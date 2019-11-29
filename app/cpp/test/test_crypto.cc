#include "../MusicPlayer/api/crypto.h"
#include "./catch2/catch.hpp"
#include <QtCore>

TEST_CASE("Factorials are computed", "[crypto]") {
    QByteArray data{"{\"radioId\":\"336355127\",\"limit\":30,\"offset\":0,"
                    "\"asc\":false,\"csrf_token\":\"\"}"};
    QByteArray key{"0CoJUm6Qyw8W8jud"};
    QByteArray iv{"0102030405060708"};
    QString result(aesEncryptCBC(data, key, iv).toBase64());
    REQUIRE(result ==
            "ms1PDBf0nrqigwsn2rvUFB/aY11qlyqriDtJme+IHNpUY051tbuVgd7bGzLZtlHKqmzVvpk+ASAVwY+8f6id68anAHlgdECyCi7A+TQ1l+U=");
}

TEST_CASE("RSA", "[crypto]") {
    QByteArray data{"{\"radioId\":\"336355127\",\"limit\":30,\"offset\":0,"
                    "\"asc\":false,\"csrf_token\":\"\"}"};
    QByteArray key{"0CoJUm6Qyw8W8jud"};
    QByteArray iv{"0102030405060708"};
    QByteArray kPublicKey("MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDgtQn2JZ34ZC28NWYpAUd98iZ37BUrX/"
                          "aKzmFbt7clFSs6sXqHauqKWqdtLkF2KexO40H1YTX8z2lSgBBOAxLsvaklV8k4cBFK9snQXE9/"
                          "DDaFt6Rr7iVZMldczhC0JNgTz+"
                          "SHXT6CBHuX3e9SdB1Ua44oncaTWz7OBGLbCiK45wIDAQAB");

    QString result(rsaEncrypt(data, kPublicKey).toHex());
    REQUIRE(result == "344127d0582c87e7e0083768265e72c45a3abea1ac30c5dfd239bcace0dd1ae9e8c1361e6cfc3631a42de416927fb74cfe41615f"
                      "49ae442dadbe3d1bea5c35e3c9524cdc4935e83dc43bb772455737b35c2dd4ef19598dd0ec545fc0915729b3b0b1f0cff92a0009"
                      "b6cd9b91d05159e916c64649a8373bd19bd2232da1bb08c4");
}