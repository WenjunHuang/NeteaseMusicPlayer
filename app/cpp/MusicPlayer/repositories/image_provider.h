//
// Created by rick on 2020/2/7.
//

#pragma once
#include <QQuickAsyncImageProvider>
#include <QNetworkReply>

namespace MusicPlayer::API {


    class ImageProvider : public QQuickAsyncImageProvider {
      public:
        QQuickImageResponse* requestImageResponse(const QString& id, const QSize& requestedSize) override;
    };
}
