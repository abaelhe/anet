
#ifndef SYS_STRINGUTIL_H
#define SYS_STRINGUTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <vector>

//using namespace std;

namespace sys {

class CStringUtil {
public:
// 把string转成int
static int strToInt(const char *str, int d);
// 是整数
static int isInt(const char *str);
// 转成小写
static char *strToLower(char *str);
// 转成大写
static char *strToUpper(char *str);
// trim
static char *trim(char *str, const char *what = " ", int mode = 3);
// hash_value
static int hashCode(const char *str);
// 得到一个str的hash值的素数
static int getPrimeHash(const char *str);
// 把string以delim分隔开,放到list中
static void split(char *str, const char *delim, std::vector<char*> &list);
// urldecode
static char *urlDecode(const char *src, char *dest);
// http://murmurhash.googlepages.com/
static unsigned int murMurHash(const void *key, int len);
// 把bytes转成可读的, 如 10K 12M 等
static std::string formatByteSize(double bytes);
};
}

#endif
///////////////////END