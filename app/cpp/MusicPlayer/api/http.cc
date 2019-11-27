//
// Created by rick on 2019/11/9.
//
#include "http.h"

#include "../util/executor.h"
#include "crypto.h"
#include <iostream>
#include <thread>
#include <utility>

namespace MusicPlayer::API {
    const QVector<QString> kUserAgentList{"Mozilla/5.0 (iPhone; CPU iPhone OS 9_1 like Mac OS X) "
                                          "AppleWebKit/601.1.46 (KHTML, like Gecko) Version/9.0 Mobile/13B143 "
                                          "Safari/601.1",
                                          "Mozilla/5.0 (iPhone; CPU iPhone OS 9_1 like Mac OS X) "
                                          "AppleWebKit/601.1.46 (KHTML, like Gecko) Version/9.0 Mobile/13B143 "
                                          "Safari/601.1",
                                          "Mozilla/5.0 (Linux; Android 5.0; SM-G900P Build/LRX21T) "
                                          "AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Mobile "
                                          "Safari/537.36",
                                          "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) "
                                          "AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Mobile "
                                          "Safari/537.36",
                                          "Mozilla/5.0 (Linux; Android 5.1.1; Nexus 6 Build/LYZ28E) "
                                          "AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Mobile "
                                          "Safari/537.36",
                                          "Mozilla/5.0 (iPhone; CPU iPhone OS 10_3_2 like Mac OS X) "
                                          "AppleWebKit/603.2.4 (KHTML, like Gecko) Mobile/14F89;GameHelper",
                                          "Mozilla/5.0 (iPhone; CPU iPhone OS 10_0 like Mac OS X) "
                                          "AppleWebKit/602.1.38 (KHTML, like Gecko) Version/10.0 Mobile/14A300 "
                                          "Safari/602.1",
                                          "Mozilla/5.0 (iPad; CPU OS 10_0 like Mac OS X) AppleWebKit/602.1.38 "
                                          "(KHTML, like Gecko) Version/10.0 Mobile/14A300 Safari/602.1",
                                          "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:46.0) Gecko/20100101 "
                                          "Firefox/46.0",
                                          "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_5) AppleWebKit/537.36 "
                                          "(KHTML, like Gecko) Chrome/59.0.3071.115 Safari/537.36",
                                          "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_5) AppleWebKit/603.2.4 "
                                          "(KHTML, like Gecko) Version/10.1.1 Safari/603.2.4",
                                          "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:46.0) Gecko/20100101 "
                                          "Firefox/46.0",
                                          "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, "
                                          "like Gecko) Chrome/51.0.2704.103 Safari/537.36",
                                          "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, "
                                          "like Gecko) Chrome/42.0.2311.135 Safari/537.36 Edge/13.10586"};

    const int kHttpRequestEventType = QEvent::registerEventType();

    class HttpRequestEvent : public QEvent {
      public:
        HttpRequestEvent(
            HttpMethod method, QUrl url, RequestOption option, QVariantHash data, folly::Promise<QNetworkReply*>&& promise)
            : QEvent((QEvent::Type)kHttpRequestEventType), method{method}, url{std::move(url)}, option{std::move(option)},
              data{std::move(data)}, promise{std::move(promise)} {}

        HttpMethod method;
        QUrl url;
        RequestOption option;
        QVariantHash data;
        folly::Promise<QNetworkReply*> promise;
    };

    QString httpMethodName(const HttpMethod& method) {
        if (method == HttpMethod::GET) {
            return "GET";
        } else if (method == HttpMethod::POST) {
            return "POST";
        } else if (method == HttpMethod::PUT) {
            return "PUT";
        }
        return "";
    }

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

    HttpWorker* HttpWorker::_instance = nullptr;

    HttpWorker::HttpWorker() : _network{new QNetworkAccessManager} {
        auto executor = Util::AppExecutor::instance();
        //      _network->setProxy(QNetworkProxy(QNetworkProxy::Socks5Proxy,"127.0.0.1",8889));
        _network->moveToThread(executor->getIOThread());
        //        _network->setParent(this);
        moveToThread(executor->getIOThread());
    }

    bool HttpWorker::event(QEvent* ev) {
        if (ev->type() == kHttpRequestEventType) {
            auto requestEvent = dynamic_cast<HttpRequestEvent*>(ev);

            QNetworkRequest request(requestEvent->url);

            //                  QSslConfiguration config;
            //                  config.setPeerVerifyMode(QSslSocket::VerifyNone);
            //                  config.setProtocol(QSsl::TlsV1SslV3);
            //                  request.setSslConfiguration(config);

            request.setHeader(QNetworkRequest::UserAgentHeader, chooseUserAgent(requestEvent->option.ua));
            request.setRawHeader(QByteArray("Referer"), QByteArray("https://music.163.com"));

            //设置认证cookie
            if (requestEvent->option.cookie) {
                std::visit(
                    [&](const auto& cookie) {
                        if constexpr (std::is_convertible_v<decltype(cookie), QString>) {
                            request.setRawHeader(QByteArray("Cookie"), cookie.toUtf8());
                        } else if (std::is_convertible_v<decltype(cookie), QHash<QString, QString>>) {
                            QByteArrayList list;
                            for (auto value = cookie.cbegin(); value != cookie.cend(); value++) {
                                list.append(QString("%1=%2").arg(value.key()).arg(value.value()).toUtf8());
                            }
                            request.setRawHeader(QByteArray("Cookie"), list.join(';'));
                        }
                    },
                    requestEvent->option.cookie.value());
            }

            QNetworkReply* reply = nullptr;
            if (requestEvent->method == HttpMethod::GET) {
                reply = _network->get(request);
            } else if (requestEvent->method == HttpMethod::POST) {
                request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

                QByteArray content;
                if (requestEvent->option.cryptoType == CryptoType::WEAPI) {

                    // 设置认证字段
                    QRegExp re{R"(_csrf=([^(;|$)]+))"};
                    if (auto pos = re.indexIn(request.rawHeader("Cookie")); pos != -1) {
                        requestEvent->data["csrf_token"] = re.cap(1);
                    } else {
                        requestEvent->data["csrf_token"] = QString("");
                    }
                    content = weapi(requestEvent->data);
                } else if (requestEvent->option.cryptoType == CryptoType::LINUX_API) {
                    QVariantHash linuxData{{"method", httpMethodName(requestEvent->method)},
                                           {"url", requestEvent->url},
                                           {"params", requestEvent->data}};
                    content = linuxApi(linuxData);
                    request.setHeader(QNetworkRequest::UserAgentHeader,
                                      QLatin1Literal("Mozilla/5.0 (X11; Linux x86_64) "
                                                     "AppleWebKit/537.36 (KHTML, like Gecko) "
                                                     "Chrome/60.0.3112.90 Safari/537.36"));
                    request.setUrl(QUrl(QLatin1Literal("https://music.163.com/api/linux/forward")));
                }

                reply = _network->post(request, content);
            }

            QObject::connect(reply, &QNetworkReply::finished, [reply, promise = std::move(requestEvent->promise)]() mutable {
                promise.setValue(reply);
            });
            return true;
        }

        return QObject::event(ev);
    } // namespace MusicPlayer::API

    folly::SemiFuture<QNetworkReply*> HttpWorker::post(QUrl&& url, RequestOption&& option, QVariantHash&& data) {
        folly::Promise<QNetworkReply*> promise;
        auto f = promise.getSemiFuture();
        request(HttpMethod::POST, std::move(url), std::move(option), std::move(data), std::move(promise));

        return f;
    }

    void HttpWorker::initInstance() {
        if (!_instance) {
            _instance = new HttpWorker;
            qRegisterMetaType<HttpMethod>("HttpMethod");
            qRegisterMetaType<RequestOption>("RequestOption");
            //            qRegisterMetaType<QFutureInterface<QNetworkReply*>>(
            //                "QFutureInterface<QNetworkReply*>");
        }
    }

    void HttpWorker::freeInstance() {
        if (_instance) {
            delete _instance;
            _instance = nullptr;
        }
    }

    HttpWorker* HttpWorker::instance() { return _instance; }

    void HttpWorker::request(
        HttpMethod method, QUrl&& url, RequestOption&& option, QVariantHash&& data, folly::Promise<QNetworkReply*>&& promise) {
        QCoreApplication::postEvent(
            this, new HttpRequestEvent(method, std::move(url), std::move(option), std::move(data), std::move(promise)));
    }
}