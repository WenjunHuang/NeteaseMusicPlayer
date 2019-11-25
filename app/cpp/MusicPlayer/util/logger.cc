//
// Created by rick on 2019/11/10.
//

#include "logger.h"
#include <QDateTime>

namespace {
    //    template<typename T>
    //    QVector<T> loadFromBuffer(const
    //    boost::circular_buffer_space_optimized<T> &src, int offset = 0) {
    //      QVector<T> ret;
    //      ret.reserve(src.size() - offset);
    //      std::copy((src.begin() + offset), src.end(),
    //      std::back_inserter(ret)); return ret;
    //    }
}
namespace MusicPlayer::Util {
    Logger* Logger::_instance = nullptr;

    void Logger::initInstance() {
        if (!_instance)
            _instance = new Logger;
    }

    void Logger::freeInstance() {
        if (_instance) {
            delete _instance;
            _instance = nullptr;
        }
    }

    Logger* Logger::instance() { return _instance; }

    void Logger::addMessage(const QString& message, const MsgType& type) {
        //      QWriteLocker locker{&_lock};
        //      const Msg msg = {
        //        _msgCounter++,
        //        QDateTime::currentMSecsSinceEpoch(),
        //        type,
        //        message.toHtmlEscaped()
        //      };
        //      _messages.push_back(msg);
        //      locker.unlock();
        //
        //      emit newLogMessage(msg);
    }

    QVector<Msg> Logger::getMessages(const int lastKnownId) const {
        //      QReadLocker locker{&_lock};
        //
        //      auto diff = _msgCounter - lastKnownId - 1;
        //      auto size = _messages.size();
        //
        //      if ((lastKnownId == -1) || (diff >= size))
        //        return loadFromBuffer(_messages);
        //
        //      if (diff <= 0)
        //        return {};
        //
        //      return loadFromBuffer(_messages, (size - diff));
        return QVector<Msg>();
    }

    Logger::Logger() {}
} // namespace MusicPlayer::Util
