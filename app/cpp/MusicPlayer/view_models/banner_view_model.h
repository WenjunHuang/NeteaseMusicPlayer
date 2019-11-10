//
// Created by rick on 2019/11/9.
//

#pragma once


#include <QtCore/QObject>
#include <QtQml/QQmlParserStatus>
#include <QtCore/QAbstractListModel>
#include "../api/data/banner.h"
#include "../api/api.h"
#include "../asyncfuture.h"

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

        BannerImageList *_bannerModel;
    };
}



