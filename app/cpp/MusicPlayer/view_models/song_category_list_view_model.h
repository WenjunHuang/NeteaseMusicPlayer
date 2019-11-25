//
// Created by rick on 2019/11/13.
//

#pragma once
#include <QtCore/QObject>
#include <QtQml/QQmlParserStatus>

namespace MusicPlayer::ViewModels {
    struct SongSubCategory {
        Q_GADGET
        Q_PROPERTY(QString name MEMBER name)
      public:
        QString name;
    };
    struct SongCategory {
      public:
        QString name;
        QVector<SongSubCategory> subCategories;
    };

    class SongCategoryListViewModel : public QObject, public QQmlParserStatus {
        Q_OBJECT
        Q_INTERFACES(QQmlParserStatus)
      public:
        explicit SongCategoryListViewModel(QObject* parent = nullptr)
            : QObject(parent) {}
        ~SongCategoryListViewModel() = default;
        void classBegin() override {}
        void componentComplete() override {}
      private:
    };
} // namespace MusicPlayer::ViewModels
