#include "StackDB.h"
void StackAssert(Stack_t* stk)
{
    if(stk == NULL)
    {
        fprintf(stderr, "Stack pointer is NULL");
        assert(0);
    }

    if(!StackError(stk))
    {
        StackDump(stk);
        assert(0);
    }
}