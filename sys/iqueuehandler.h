
#ifndef SYS_QUEUE_HANDLER_H_
#define SYS_QUEUE_HANDLER_H_

namespace sys {

class IQueueHandler {
public:
virtual ~IQueueHandler() {}
virtual bool handleQueue(void *data, int len, int threadIndex, void *args) = 0;
};

}

#endif /*SYS_QUEUE_HANDLER_H_*/