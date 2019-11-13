//
// Created by rick on 2019/11/13.
//

#pragma once
#include <QtCore/QObject>
#include <QtQml/QQmlParserStatus>

namespace MusicPlayer::ViewModels {
    class SongCategoryListViewModel : public QObject, public QQmlParserStatus {
        Q_OBJECT
        Q_INTERFACES(QQmlParserStatus)
      public:
        explicit SongCategoryListViewModel(QObject* parent = nullptr)
            : QObject(parent) {}
        ~SongCategoryListViewModel() = default;
        void classBegin() override {}
        void componentComplete() override {}
    };
} // namespace MusicPlayer::ViewModels
