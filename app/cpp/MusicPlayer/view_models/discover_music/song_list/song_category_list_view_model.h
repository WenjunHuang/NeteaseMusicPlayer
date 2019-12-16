//
// Created by rick on 2019/11/13.
//

#pragma once
#include ""
#include "../../../api/api.h"
#include "../../../util/util.h"
#include "../../states.h"
#include "../../base_state_view_model.h"
#include <QtCore>
#include <QtQml/QQmlParserStatus>

namespace MusicPlayer::ViewModels {
    using namespace MusicPlayer::API;
    using namespace MusicPlayer::Service;
    using namespace MusicPlayer::Util;

    struct SongCategoryListViewModelReadyStateCategoryItem {
        Q_GADGET
        Q_PROPERTY(QString name MEMBER name)
        Q_PROPERTY(bool hot MEMBER hot)
      public:
        QString name;
        bool hot;

        bool operator==(const SongCategoryListViewModelReadyStateCategoryItem& other) const;

        bool operator!=(const SongCategoryListViewModelReadyStateCategoryItem& other) const;
    };

    struct SongCategoryListViewModelReadyStateCategory {
        Q_GADGET
        Q_PROPERTY(QString name MEMBER name)
        Q_PROPERTY(int category MEMBER category)
        Q_PROPERTY(QVariantList items MEMBER items)
      public:
        QString name;
        int category;
        QVariantList items; // SongCategoryListViewModelReadyStateCategoryItem

        bool operator==(const SongCategoryListViewModelReadyStateCategory& other) const;

        bool operator!=(const SongCategoryListViewModelReadyStateCategory& other) const;
    };

    struct SongCategoryListViewModelReadyState {
        Q_GADGET
        Q_PROPERTY(QString allName MEMBER allName)
        Q_PROPERTY(QVariantList categories MEMBER categories)
        Q_PROPERTY(QVector<QString> hotCategories MEMBER hotCategories)
      public:
        QString allName;
        QVariantList categories; // SongCategoryListViewModelReadyStateCategory
        QVector<QString> hotCategories;

        bool operator==(const SongCategoryListViewModelReadyState& other) const;

        bool operator!=(const SongCategoryListViewModelReadyState& other) const;
    };

    class SongCategoryListViewModel : public BaseStateViewModel, public QQmlParserStatus {
        Q_OBJECT
        Q_INTERFACES(QQmlParserStatus)
        Q_PROPERTY(QVariant state READ state NOTIFY stateChanged)
      public:
        explicit SongCategoryListViewModel(QObject* parent = nullptr) : BaseStateViewModel(parent) {}

        void classBegin() override {}

        void componentComplete() override;

        Q_INVOKABLE void reload();

        static void registerMetaTypes();
    };
} // namespace MusicPlayer::ViewModels

Q_DECLARE_METATYPE(MusicPlayer::ViewModels::SongCategoryListViewModelReadyStateCategory)
Q_DECLARE_METATYPE(MusicPlayer::ViewModels::SongCategoryListViewModelReadyState)
Q_DECLARE_METATYPE(MusicPlayer::ViewModels::SongCategoryListViewModelReadyStateCategoryItem)
