//
// Created by rick on 2019/11/9.
//

#include "banner_view_model.h"
#include "../../../util/executor.h"

namespace MusicPlayer::ViewModels {
    using namespace MusicPlayer::Util;

    class BannerImageList : public QAbstractListModel {
        Q_OBJECT

      public:
        enum Roles { ImageUrl = Qt::UserRole + 1, TargetId, TargetType, TitleColor, TypeTitle, EncodeId };

        BannerImageList(QObject* parent);

        int rowCount(const QModelIndex& parent) const override;

        QVariant data(const QModelIndex& index, int role) const override;

        QHash<int, QByteArray> roleNames() const override;

        void setBannersData(const APIBannersData& banners) {
            beginResetModel();
            _bannerData.clear();
            _bannerData.append(banners.banners);
            endResetModel();
        }

      private:
        QVector<APIBannerData> _bannerData;
    };

    int BannerImageList::rowCount(const QModelIndex& parent) const { return _bannerData.size(); }

    QVariant BannerImageList::data(const QModelIndex& index, int role) const {
        if (role == Roles::ImageUrl) {
            return _bannerData[index.row()].imageUrl;
        } else if (role == Roles::TypeTitle) {
            return _bannerData[index.row()].typeTitle;
        } else if (role == Roles::TitleColor) {
            return _bannerData[index.row()].titleColor;
        } else if (role == Roles::TargetType) {
            return _bannerData[index.row()].targetType;
        } else if (role == Roles::TargetId) {
            return _bannerData[index.row()].targetId;
        } else if (role == Roles::EncodeId) {
            return _bannerData[index.row()].encodeId;
        }
        return {};
    }

    QHash<int, QByteArray> BannerImageList::roleNames() const {
        QHash<int, QByteArray> names;
        names[EncodeId]   = "encodeId";
        names[ImageUrl]   = "imageUrl";
        names[TargetId]   = "targetId";
        names[TargetType] = "targetType";
        names[TitleColor] = "titleColor";
        names[TypeTitle]  = "typeTitle";

        return names;
    }

    BannerImageList::BannerImageList(QObject* parent) : QAbstractListModel(parent) {}

    void BannerViewModel::componentComplete() {
        qDebug() << "complete";
        loadBannerData();
    }

    void BannerViewModel::classBegin() {}

    BannerViewModel::BannerViewModel(QObject* parent) : QObject(parent) { _bannerModel = new BannerImageList(this); }

    int BannerViewModel::bannerCount() const { return _bannerModel->rowCount(QModelIndex()); }

    void BannerViewModel::loadBannerData() {
        if (_loading && !_loading->isReady())
            return; // 还在加载中

        MusicAPI api;
        _loading = api.banner()
                       .via(AppExecutor::instance()->getMainExecutor().get())
                       .thenValue([this](Response<APIBannersData>&& reply) {
                           std::visit(
                               [=](const auto& value) {
                                   if constexpr (std::is_convertible_v<decltype(value), APIBannersData>) {
                                       _bannerModel->setBannersData(value);
                                       bannerCountChanged();
                                   } else {
                                       // errors
                                   }
                               },
                               reply);
                           return std::nullopt;
                       });
    }

    QAbstractListModel* BannerViewModel::bannerModel() { return _bannerModel; }
} // namespace MusicPlayer::ViewModels
#include "banner_view_model.moc"