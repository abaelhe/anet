
#ifndef SYS_CONFIG_H
#define SYS_CONFIG_H

#include <string>
#include <ext/hash_map>
#include "stringutil.h"
#include "log.h"

//using namespace std;
//using namespace __gnu_cxx;

namespace sys {
struct str_hash {
size_t operator()(const std::string& str) const {
return __gnu_cxx::__stl_hash_string(str.c_str());
}
};
struct char_equal {
bool operator()(const char* s1, const char* s2) const {
return strcmp(s1, s2) == 0;
}
};
typedef __gnu_cxx::hash_map<std::string, std::string, str_hash> STR_STR_MAP;
typedef STR_STR_MAP::iterator STR_STR_MAP_ITER;
typedef __gnu_cxx::hash_map<std::string, STR_STR_MAP*, str_hash> STR_MAP;
typedef STR_MAP::iterator STR_MAP_ITER;

#define SYS_CONFIG sys::CConfig::getCConfig()

class           CConfig {
public:
CConfig();
~CConfig();

// 加载一个文件
int load(const char *filename);
// 取一个字符串
const char *getString(const char *section, const std::string& key, const char *d = NULL);
// 取一string列表
std::vector<const char*> getStringList(const char *section, const std::string& key);
// 取一个整型
int getInt(char const *section, const std::string& key, int d = 0);
// 取一整型列表
std::vector<int> getIntList(const char *section, const std::string& key);
// 取一section下所有的key
int getSectionKey(const char *section, std::vector<std::string> &keys);
// 得到所有section的名字
int getSectionName(std::vector<std::string> &sections);
// 完整的配置文件字符串
std::string toString();
// 得到静态实例
static CConfig& getCConfig();

private:
// 两层map
STR_MAP m_configMap;

private:
// 解析字符串
int parseValue(char *str, char *key, char *val);
char *isSectionName(char *str);
};
}

#endif