
#ifndef SYS_EVENTHANDLER_H
#define SYS_EVENTHANDLER_H

namespace util
{
class ThreadPool;
class ThreadPoolWorkItem
{
public:
virtual ~ThreadPoolWorkItem(){}
virtual void destroy( )=0;
virtual void execute( const ThreadPool* ) = 0;
};
}
#endif