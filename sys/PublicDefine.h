
#ifndef SYS_PUBLIC_DEFINE_H_
#define SYS_PUBLIC_DEFINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>

namespace sys
{
#define MAX_FILENAME_LEN 256
#define TIME_MAX INT_MAX


#define JUST_CONTINUE(ContCond) \
if (ContCond) \
continue
#define PRINT_CONTINUE(ContCond, Module, Level, ...) \
if (ContCond) \
{ \
Print(Module, Level, __VA_ARGS__); \
continue; \
}

#define JUST_BREAK(BreakCond) \
if (BreakCond) \
break
#define PRINT_BREAK(BreakCond, Module, Level, ...) \
if (BreakCond) \
{ \
Print(Module, Level, __VA_ARGS__); \
break; \
}

#define JUST_RETURN(RetCond, Ret) \
if (RetCond) \
return Ret

#define PRINT_RETURN(RetCond, Ret, Module, Level, ...) \
do \
{ \
if (RetCond) \
{ \
Print(Module, Level, __VA_ARGS__); \
return Ret; \
} \
} \
while (0)

#define OUTPUT_RETURN(RetCond,Ret,output,value)\
do\
{\
if (RetCond )\
{\
output->writeInt16( value );\
return Ret;\
}\
}\
while(0);

#define OUTPUTPRINT_RETURN(RetCond,Ret,output,value,Module,Level,...)\
do\
{\
if ( RetCond )\
{\
output->writeInt16( value );\
Print(Module, Level, __VA_ARGS__); \
return Ret;\
}\
}while(0);


#define C_TRY(ExceptionCond) \
if (ExceptionCond) \
goto labelException

#define C_PRINT_TRY(ExceptionCond, Module, Level, ...) \
do \
{ \
if (ExceptionCond) \
{ \
Print(Module, Level, __VA_ARGS__); \
goto labelException; \
} \
} \
while (0)

#define C_CATCH \
goto labelException; \
labelException:


// return without running clear code
#define RETURN_ERROR(ErrorCond) \
if (ErrorCond) \
goto labelClearEnd
// return with running clear code
#define GOTO_CLEAR(ErrorCond) \
if (ErrorCond) \
goto labelClearBegin
#define RETURN_PRINT_ERROR(ErrorCond, Module, Level, ...) \
do \
{ \
if (ErrorCond) \
{ \
Print(Module, Level, __VA_ARGS__); \
goto labelClearEnd; \
} \
} \
while (0)
#define GOTO_PRINT_CLEAR(ErrorCond, Module, Level, ...) \
do \
{ \
if (ErrorCond) \
{ \
Print(Module, Level, __VA_ARGS__); \
goto labelClearBegin; \
} \
} \
while (0)
#define CLEAR_BEGIN \
{ \
#define CLEAR_END \
labelClearEnd:; \
}

}//end namespace
#endif // PUBLIC_DEFINE_H_