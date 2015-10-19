
#ifndef SYS_TIMEUTIL_H_
#define SYS_TIMEUTIL_H_

#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>

namespace sys {

class CTimeUtil {
public:
static int64_t getTime();
static int64_t getMonotonicTime();
static char *timeToStr(time_t t, char *dest);
static int strToTime(char *str);
};

}

#endif