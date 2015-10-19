
#ifndef SYS_PROCESS_H
#define SYS_PROCESS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <log.h>

namespace sys {

class CProcess {

public:
// 起一个daemon
static int startDaemon(const char *szPidFile, const char *szLogFile);
// 进程是不是存在
static int existPid(const char *szPidFile);
// 写PID文件
static void writePidFile(const char *szPidFile);
};
}
#endif
