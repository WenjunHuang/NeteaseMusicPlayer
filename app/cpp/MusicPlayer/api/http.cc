//
// Created by rick on 2019/11/9.
//
#include <QRandomGenerator>
#include <QNetworkCookie>
#include <QtCore/QUrlQuery>
#include <QtNetwork/QNetworkProxy>
#include "http.h"
#include "crypto.h"

namespace MusicPlayer::API {
    const QVector<QString> kUserAgentList{
      "Mozilla/5.0 (iPhone; CPU iPhone OS 9_1 like Mac OS X) AppleWebKit/601.1.46 (KHTML, like Gecko) Version/9.0 Mobile/13B143 Safari/601.1",
      "Mozilla/5.0 (iPhone; CPU iPhone OS 9_1 like Mac OS X) AppleWebKit/601.1.46 (KHTML, like Gecko) Version/9.0 Mobile/13B143 Safari/601.1",
      "Mozilla/5.0 (Linux; Android 5.0; SM-G900P Build/LRX21T) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Mobile Safari/537.36",
      "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Mobile Safari/537.36",
      "Mozilla/5.0 (Linux; Android 5.1.1; Nexus 6 Build/LYZ28E) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Mobile Safari/537.36",
      "Mozilla/5.0 (iPhone; CPU iPhone OS 10_3_2 like Mac OS X) AppleWebKit/603.2.4 (KHTML, like Gecko) Mobile/14F89;GameHelper",
      "Mozilla/5.0 (iPhone; CPU iPhone OS 10_0 like Mac OS X) AppleWebKit/602.1.38 (KHTML, like Gecko) Version/10.0 Mobile/14A300 Safari/602.1",
      "Mozilla/5.0 (iPad; CPU OS 10_0 like Mac OS X) AppleWebKit/602.1.38 (KHTML, like Gecko) Version/10.0 Mobile/14A300 Safari/602.1",
      "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:46.0) Gecko/20100101 Firefox/46.0",
      "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Safari/537.36",
      "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_5) AppleWebKit/603.2.4 (KHTML, like Gecko) Version/10.1.1 Safari/603.2.4",
      "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:46.0) Gecko/20100101 Firefox/46.0",
      "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36",
      "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.135 Safari/537.36 Edge/13.10586"
    };

    QString chooseUserAgent(std::optional<UserAgentType> ua) {
      int index = -1;
      if (!ua) {
        index = QRandomGenerator::global()->bounded(kUserAgentList.size());
      } else if (ua.value() == UserAgentType::Mobile) {
        index = QRandomGenerator::global()->bounded(8);
      } else {
        index = QRandomGenerator::global()->bounded(8, kUserAgentList.size());
      }

      return kUserAgentList[index];
    }

    HttpWorker::HttpWorker(QObject *parent)
      : QObject{parent}, _network{new QNetworkAccessManager} {

      _worker = new QThread;
      _worker->setObjectName("HttpWorker");
//      _network->setProxy(QNetworkProxy(QNetworkProxy::Socks5Proxy,"127.0.0.1",8889));
      _network->moveToThread(_worker);
      moveToThread(_worker);

      connect(this, &HttpWorker::_request, this,
              [this](HttpMethod method,
                     QUrl url,
                     const RequestOption &option,
                     QVariantHash data,
                     QFutureInterface<QNetworkReply *> result) {
                  result.setExpectedResultCount(1);
                  result.reportStarted();

                  QNetworkRequest request(url);

//                  QSslConfiguration config;
//                  config.setPeerVerifyMode(QSslSocket::VerifyNone);
//                  config.setProtocol(QSsl::TlsV1SslV3);
//                  request.setSslConfiguration(config);

                  request.setHeader(QNetworkRequest::UserAgentHeader, chooseUserAgent(option.ua));
                  request.setRawHeader(QByteArray("Referer"), QByteArray("https://music.163.com"));

                  //设置认证cookie
                  if (option.cookie) {
                    std::visit([&](const auto &cookie) {
                        if constexpr (std::is_convertible_v<decltype(cookie), QString>) {
                          request.setRawHeader(QByteArray("Cookie"), cookie.toUtf8());
                        } else if (std::is_convertible_v<decltype(cookie), QHash<QString, QString>>) {
                          QByteArrayList list;
                          for (auto value = cookie.cbegin(); value != cookie.cend(); value++) {
                            list.append(QString("%1=%2").arg(value.key()).arg(value.value()).toUtf8());
                          }
                          request.setRawHeader(QByteArray("Cookie"), list.join(';'));
                        }
                    }, option.cookie.value());
                  }
                  data["csrf_token"] = QString("");

                  QNetworkReply *reply = nullptr;
                  if (method == HttpMethod::GET) {
                    reply = _network->get(request);
                  } else if (method == HttpMethod::POST) {
                    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

                    QByteArray content;
                    if (option.cryptoType == CryptoType::WEAPI)
                      content = weapi(data);

                    reply = _network->post(request, content);
                  }

                  QObject::connect(reply, &QNetworkReply::finished,
                                   [reply, result]() mutable {
                                       result.reportResult(reply);
                                       result.reportFinished();
                                   });
              });
      _worker->start();
    }


    QFuture<QNetworkReply *>
    HttpWorker::post(QUrl url, RequestOption option, const QHash<QString, QVariant> &data) {
      QFutureInterface<QNetworkReply *> promise;
      emit _request(HttpMethod::POST, url, option, data, promise);
      return promise.future();
    }
}