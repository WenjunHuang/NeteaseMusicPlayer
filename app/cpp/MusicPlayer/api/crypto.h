#include <QByteArray>

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

QByteArray aesEncryptCBC(const QByteArray& buffer, const QByteArray& key,
                         const QByteArray& iv);
QByteArray aseEncryptECB(const QByteArray& buffer, const QByteArray& key);
QByteArray rsaEncrypt(const QByteArray& buffer, const QByteArray& key);