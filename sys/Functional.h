
#ifndef SYS_FUNCTIONAL_H
#define SYS_FUNCTIONAL_H

#include "Handle.h"
#include <functional>

namespace util
{
template<class R, class T, class H>
class ConstMemFun : public std::unary_function<H, R>
{
typedef R (T::*MemberFN)(void) const;
MemberFN _mfn;

public:

explicit ConstMemFun(MemberFN p) : _mfn(p) { }
R operator()(H handle) const
{
return (handle.get() ->* _mfn)();
}
};

template<class R, class T>
inline ConstMemFun<R, T, Handle<T> >
constMemFun(R (T::*p)(void) const)
{
return ConstMemFun<R, T, Handle<T> >(p);
}
}//end namespace
#endif