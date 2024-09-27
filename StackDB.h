#ifndef STACK_DB
#define STACK_DB

#include "stack.h"

#ifdef NDEBUG
#define ON_DEBUG(code) code
#else
#define ON_DEBUG(code)
#endif


void StackAssert(Stack_t* stk);
int StackError(Stack_t* stk);

#endif



int StackError(Stack_t* stk)
{

}