#include "stack.h"

int main()
{
    Stack_t stk = {};
    StackInit(&stk, 129);
    for(int i = 0; i < 199; i++)
    {
        StackPush(&stk, 69.69);
    }

    StackDump(stk);
    double x = 0;
    StackPop(&stk, &x);
    StackDump(stk);

    if(StackDtor(&stk) != 0)
    {
        assert(0);
        exit(DESTRUCTOR_ERROR);
    }

    MWHS;
    return 0;
}


