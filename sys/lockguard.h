
#ifndef SYS_LOCK_GUARD_H_
#define SYS_LOCK_GUARD_H_

namespace sys
{
template <class T>
class CLockGuard
{
public:
CLockGuard(const T& lock, bool block = true) : _lock(lock)
{
_acquired = !(block ? _lock.lock() : _lock.tryLock());
}

~CLockGuard()
{
_lock.unlock();
}

bool acquired() const
{
return _acquired;
}

private:
const T& _lock;
mutable bool _acquired;
};
}

#endif