//
// Created by rick on 2019/11/10.
//

#include "misc.h"
#ifdef Q_OS_WIN
#include <windows.h>
#include <powrprof.h>
#include <Shlobj.h>
#else
#include <unistd.h>
#endif

#ifdef Q_OS_MACOS
#include <Carbon/Carbon.h>
#include <CoreServices/CoreServices.h>
#endif

namespace MusicPlayer::Util {
    QString getUserIDString() {
      QString uid = "0";
#ifdef Q_OS_WIN
      const int UNLEN = 256;
        WCHAR buffer[UNLEN + 1] = {0};
        DWORD buffer_len = sizeof(buffer) / sizeof(*buffer);
        if (GetUserNameW(buffer, &buffer_len))
            uid = QString::fromWCharArray(buffer);
#else
      uid = QString::number(getuid());
#endif
      return uid;
    }
}