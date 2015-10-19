
#ifndef SYS_THREADEXCEPTION_H
#define SYS_THREADEXCEPTION_H
#include "Exception.h"
#include "Time.h"

namespace util
{
class ThreadSyscallException : public SyscallException
{
public:

ThreadSyscallException(const char*, int, int);
virtual std::string name() const;
virtual Exception* clone() const;
virtual void _throw() const;

private:

static const char* _name;
};

class ThreadLockedException : public Exception
{
public:

ThreadLockedException(const char*, int);
virtual std::string name() const;
virtual Exception* clone() const;
virtual void _throw() const;

private:

static const char* _name;
};

class ThreadStartedException : public Exception
{
public:

ThreadStartedException(const char*, int);
virtual std::string name() const;
virtual Exception* clone() const;
virtual void _throw() const;

private:

static const char* _name;
};

class ThreadNotStartedException : public Exception
{
public:

ThreadNotStartedException(const char*, int);
virtual std::string name() const;
virtual Exception* clone() const;
virtual void _throw() const;

private:

static const char* _name;
};

class BadThreadControlException : public Exception
{
public:

BadThreadControlException(const char*, int);
virtual std::string name() const;
virtual Exception* clone() const;
virtual void _throw() const;

private:

static const char* _name;
};

class InvalidTimeoutException : public Exception
{
public:

InvalidTimeoutException(const char*, int, const Time&);
virtual std::string name() const;
virtual void print(std::ostream&) const;
virtual Exception* clone() const;
virtual void _throw() const;

private:

Time _timeout;
static const char* _name;
};

class ThreadCreateException: public Exception
{
public:
ThreadCreateException( const char* , int );
virtual std::string name() const;
virtual void print(std::ostream&) const;
virtual Exception* clone() const;
virtual void _throw() const;
private:
static const char* _name;
};
}//end namespace
#endif
