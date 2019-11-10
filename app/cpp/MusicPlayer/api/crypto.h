#include <QByteArray>
#include <QVariantHash>

QByteArray aesEncryptCBC(const QByteArray &buffer, const QByteArray &key,
                         const QByteArray &iv);

QByteArray aseEncryptECB(const QByteArray &buffer, const QByteArray &key);

QByteArray rsaEncrypt(const QByteArray &buffer, const QByteArray &key);

QByteArray weapi(const QVariantHash &data);

QByteArray linuxApi(const QVariantHash &data);