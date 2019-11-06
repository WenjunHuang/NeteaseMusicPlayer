#include <QByteArray>

inline QByteArray iv("0102030405060708");
inline QByteArray presetKey("0CoJUm6Qyw8W8jud");
inline QByteArray linuxapiKey("rFgB&h#%2?^eDg:Q");
inline QByteArray base62("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
inline QByteArray publicKey(
    "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDgtQn2JZ34ZC28NWYpAUd98iZ37BUrX/"
    "aKzmFbt7clFSs6sXqHauqKWqdtLkF2KexO40H1YTX8z2lSgBBOAxLsvaklV8k4cBFK9snQXE9/"
    "DDaFt6Rr7iVZMldczhC0JNgTz+"
    "SHXT6CBHuX3e9SdB1Ua44oncaTWz7OBGLbCiK45wIDAQAB");
inline QByteArray eapiKey("e82ckenh8dichen8");

QByteArray aesEncryptCBC(const QByteArray &buffer, const QByteArray &key,const QByteArray& iv);
QByteArray aseEncryptECB(const QByteArray& buffer, const QByteArray& key);
QByteArray rsaEncrypt(const QByteArray& buffer, const QByteArray& key);