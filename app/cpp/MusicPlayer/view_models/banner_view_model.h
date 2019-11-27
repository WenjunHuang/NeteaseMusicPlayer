//
// Created by rick on 2019/11/9.
//

#pragma once


#include <QtCore>
#include <QtQml>
#include <folly/futures/Future.h>
#include "../api/data/banner.h"
#include "../api/api.h"

namespace MusicPlayer::ViewModels {
    using namespace MusicPlayer::API;

    class BannerImageList;

    class BannerViewModel : public QObject, public QQmlParserStatus {
    Q_OBJECT
        Q_INTERFACES(QQmlParserStatus)
        Q_PROPERTY(int bannerCount
                     READ
                       bannerCount
                     NOTIFY
                     bannerCountChanged)
        Q_PROPERTY(QAbstractListModel *banners
                     READ
                     bannerModel)
    public:
        BannerViewModel(QObject *parent = nullptr);

        void componentComplete() override;

        void classBegin() override;

        int bannerCount() const;

        QAbstractListModel* bannerModel();

    signals:
        void bannerCountChanged();

    private:
        void loadBannerData();

        std::optional<folly::Future<bool>> _loading;

        BannerImageList *_bannerModel;
    };
}



