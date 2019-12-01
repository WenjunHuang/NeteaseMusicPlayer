//
// Created by rick on 2019/11/13.
//

#pragma once
#include "../api/api.h"
#include "../repositories/repositories.h"
#include "../util/util.h"
#include "./states.h"
#include <QtCore>
#include <QtQml/QQmlParserStatus>

namespace MusicPlayer::ViewModels {
    using namespace MusicPlayer::API;
    using namespace MusicPlayer::Repository;
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
        Q_PROPERTY(QString icon MEMBER icon)
        Q_PROPERTY(QVariantList items MEMBER items)
      public:
        QString name;
        QString icon;
        QVariantList items; // SongCategoryListViewModelReadyStateCategoryItem

        bool operator==(const SongCategoryListViewModelReadyStateCategory& other) const;

        bool operator!=(const SongCategoryListViewModelReadyStateCategory& other) const;
    };

    struct SongCategoryListViewModelReadyState {
        Q_GADGET
        Q_PROPERTY(QString allName MEMBER allName)
        Q_PROPERTY(QVariantList categories MEMBER categories)
      public:
        QString allName;
        QVariantList categories; // SongCategoryListViewModelReadyStateCategory

        bool operator==(const SongCategoryListViewModelReadyState& other) const;

        bool operator!=(const SongCategoryListViewModelReadyState& other) const;
    };

    class SongCategoryListViewModel : public QObject, public QQmlParserStatus {
        Q_OBJECT
        Q_INTERFACES(QQmlParserStatus)
        Q_PROPERTY(QVariant state READ state NOTIFY stateChanged)
      public:
        explicit SongCategoryListViewModel(QObject* parent = nullptr) : QObject(parent) {}

        QVariant state() const { return QVariant::fromStdVariant(_state); }

        void classBegin() override {}

        void componentComplete() override;

        Q_INVOKABLE void reload();

        static void registerMetaTypes();
      signals:
        void stateChanged();

      private:
        void setState(const ViewModelState& state);
        ViewModelState _state;
    };
} // namespace MusicPlayer::ViewModels

Q_DECLARE_METATYPE(MusicPlayer::ViewModels::SongCategoryListViewModelReadyStateCategory)
Q_DECLARE_METATYPE(MusicPlayer::ViewModels::SongCategoryListViewModelReadyState)
Q_DECLARE_METATYPE(MusicPlayer::ViewModels::SongCategoryListViewModelReadyStateCategoryItem)
