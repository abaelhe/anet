
#ifndef SYS_EXCEPTION_H
#define SYS_EXCEPTION_H
#include <exception>
#include <string>
#include <ostream>

#include "sys.h"

//using namespace std;

namespace util
{
class Exception : public std::exception
{
public:

Exception();
Exception(const char*, int);
virtual ~Exception() throw();
virtual std::string name() const;
virtual void print(std::ostream&) const;
virtual const char* what() const throw();
virtual Exception* clone() const;
virtual void _throw() const;
const char* file() const;
int line() const;

private:

const char* _file;
int _line;
static const char* _name;
mutable ::std::string _str;
};

std::ostream& operator << (std::ostream& out, const Exception& ex);

class NullHandleException : public Exception
{
public:

NullHandleException(const char*, int);
virtual ~NullHandleException() throw();
virtual std::string name() const;
virtual Exception* clone() const;
virtual void _throw() const;

private:
static const char* _name;
};

class IllegalArgumentException : public Exception
{
public:

IllegalArgumentException(const char*, int);
IllegalArgumentException(const char*, int, const std::string&);
virtual ~IllegalArgumentException() throw();
virtual std::string name() const;
virtual void print(std::ostream&) const;
virtual Exception* clone() const;
virtual void _throw() const;

std::string reason() const;

private:

static const char* _name;
std::string _reason;
};

class SyscallException : public Exception
{
public:
SyscallException( const char* , int );
SyscallException(const char*, int, int);
virtual std::string name() const;
virtual void print(std::ostream&) const;
virtual Exception* clone() const;
virtual void _throw() const;

int error() ;

int _error;
static const char* _name;
};
}//end namespace
#endif