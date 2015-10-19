
#ifndef SYS_FILE_QUEUE_H
#define SYS_FILE_QUEUE_H

#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "log.h"
#include "threadmutex.h"
#include "fileutil.h"

namespace sys {

#define TBFQ_MAX_FILE_SIZE (1024*1024*16)    //16M
#define TBFQ_MAX_THREAD_COUNT 60
#define TBFQ_FILE_QUEUE_FLAG  0x31765166     // fQv1

typedef struct unsettle {
uint32_t seqno;
int offset;
} unsettle;

typedef struct queue_item {
unsettle pos;
int flag;
int len;
char data[0];
} queue_item;

typedef struct qinfo_head {
uint32_t read_seqno;    // 读文件的seqno
int read_offset;        // 读文件的offset
uint32_t write_seqno;        // 写文件的seqno
int write_filesize;     // 写文件的大小
int queue_size;         // 队列长度
int exit_status;        // 退出状态
int reserve[2];
unsettle pos[TBFQ_MAX_THREAD_COUNT]; // 正在处理的位置
} qinfo_head;

class CFileUtil;
class CFileQueue {
public:
CFileQueue(char *rootPath, char *queueName, int maxFileSize = TBFQ_MAX_FILE_SIZE);
~CFileQueue(void);
// 写入一数据
int push(void *data, int len);
// 取出一数据
queue_item *pop(uint32_t index = 0);
// 删除一数据
int clear();
// 是否空了
int isEmpty();
// 己处理完了
void finish(uint32_t index = 0);
void backup(uint32_t index = 0);

private:
// 数据文件句柄(读)
int m_readFd;
// 数据文件句柄(写)
int m_writeFd;
// 头文件句柄
int m_infoFd;
// queue的头信息
qinfo_head m_head;
// 保存的路径
char *m_queuePath;
// 最大文件多大就新写一个文件
int m_maxFileSize;

private:
// 打开数据文件写
inline int openWriteFile();
// 打开数据文件读
inline int openReadFile();
//删除处理完的文件
inline int deleteReadFile();
// 写header
inline int writeHead();
// 恢复数据
void recoverRecord();
};
}

#endif

//////////////////END