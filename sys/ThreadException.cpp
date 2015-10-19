
#include "ThreadException.h"
#include "Time.h"

using namespace std;
namespace util
{
ThreadSyscallException::ThreadSyscallException(const char* file, int line, int err ):
SyscallException(file, line, err)
{
}

const char* util::ThreadSyscallException::_name = "::ThreadSyscallException";

string ThreadSyscallException::name() const
{
return _name;
}

Exception* ThreadSyscallException::clone() const
{
return new ThreadSyscallException(*this);
}

void ThreadSyscallException::_throw() const
{
throw *this;
}

ThreadLockedException::ThreadLockedException(const char* file, int line) :
Exception(file, line)
{
}

const char* util::ThreadLockedException::_name = "::ThreadLockedException";

string ThreadLockedException::name() const
{
return _name;
}

Exception* ThreadLockedException::clone() const
{
return new ThreadLockedException(*this);
}

void ThreadLockedException::_throw() const
{
throw *this;
}

ThreadStartedException::ThreadStartedException(const char* file, int line) :
Exception(file, line)
{
}

const char* util::ThreadStartedException::_name = "::ThreadStartedException";

string ThreadStartedException::name() const
{
return _name;
}

Exception* ThreadStartedException::clone() const
{
return new ThreadStartedException(*this);
}

void ThreadStartedException::_throw() const
{
throw *this;
}

ThreadNotStartedException::ThreadNotStartedException(const char* file, int line) :
Exception(file, line)
{
}

const char* util::ThreadNotStartedException::_name = "::ThreadNotStartedException";

string ThreadNotStartedException::name() const
{
return _name;
}

Exception* ThreadNotStartedException::clone() const
{
return new ThreadNotStartedException(*this);
}

void ThreadNotStartedException::_throw() const
{
throw *this;
}


BadThreadControlException::BadThreadControlException(const char* file, int line) :
Exception(file, line)
{
}

const char* util::BadThreadControlException::_name = "::BadThreadControlException";

string BadThreadControlException::name() const
{
return _name;
}

Exception* BadThreadControlException::clone() const
{
return new BadThreadControlException(*this);
}

void BadThreadControlException::_throw() const
{
throw *this;
}

InvalidTimeoutException::InvalidTimeoutException(const char* file, int line,
const util::Time& timeout):
Exception(file, line),
_timeout(timeout)
{
}

const char* util::InvalidTimeoutException::_name = "::InvalidTimeoutException";

string InvalidTimeoutException::name() const
{
return _name;
}

void InvalidTimeoutException::print(ostream& os) const
{
Exception::print(os);
}

Exception* InvalidTimeoutException::clone() const
{
return new InvalidTimeoutException(*this);
}

void InvalidTimeoutException::_throw() const
{
throw *this;
}
const char* util::ThreadCreateException::_name="::ThreadCreateException";

ThreadCreateException::ThreadCreateException(const char* file , int line):
Exception(file,line)
{

}

string ThreadCreateException::name() const
{
return _name;
}

void ThreadCreateException::print(ostream& os ) const
{
Exception::print(os);
}

Exception* ThreadCreateException::clone() const
{
return new ThreadCreateException(*this);
}

void ThreadCreateException::_throw() const
{
throw *this;
}
}//end namespace util