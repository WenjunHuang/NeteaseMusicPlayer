//
// Created by rick on 2019/11/10.
//

#pragma once

#include <QObject>
//#include <boost/circular_buffer.hpp>
#include <QReadWriteLock>

namespace MusicPlayer::Util {
    enum class MsgType {
        ALL = -1,
        NORMAL = 0x1,
        INFO = 0x2,
        WARNING = 0x4,
        CRITICAL = 0x8
    };
    Q_DECLARE_FLAGS(MsgTypes, MsgType)
    struct Msg {
        int id;
        qint64 timestamp;
        MsgType type;
        QString message;
    };

    class Logger : public QObject {
    Q_OBJECT

        Q_DISABLE_COPY(Logger)

        Logger();

    public:
        static void initInstance();

        static void freeInstance();

        static Logger *instance();

        void addMessage(const QString &message, const MsgType &type = MsgType::NORMAL);
        QVector<Msg> getMessages(int lastKnownId = -1) const;

    signals:

        void newLogMessage(const Msg &message);

    private:
//        boost::circular_buffer_space_optimized<Msg> _messages;
        int _msgCounter = 0;
        mutable QReadWriteLock _lock;
        static Logger *_instance;

    };
}



