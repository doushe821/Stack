#ifndef STACK_DB
#define STACK_DB

#include "stack.h"

#ifdef NDEBUG
#define ON_DEBUG(code) 
#else
#define ON_DEBUG(code) code
#endif

const size_t UNLIKELY_STACK_SIZE = 666666666666666666; // Very unlikely to appear, used as a sign of stack underflow.

void StackAssert(Stack_t* stk, const char* stkName, const char* file, const char* func, int line);
int doStackDump(Stack_t* stk, const char* stkName, const char* file, const char* func, int line);
int StackError(Stack_t* stk);

#ifndef STACK_DUMP_INC
#define StackDump(stk) doStackDump((stk), #stk, __FILE__, __func__, __LINE__) 
#endif

#ifndef NDEBUG
#define STACK_ASSERT(Stack) StackAssert((Stack), #Stack, __FILE__, __func__, __LINE__)
#else
#define STACK_ASSERT(Stack)
#endif

#endif



