#include "stack.h"

int main()
{


    Stack_t stk = {};

    StackInit(&stk, 8);
    for(int i = 0; i < 9; i++)
    {
        StackPush(&stk, 1611);
    }
    StackDump(&stk);
    StackElem_t x = 0;
    for(int i  = 0; i < 7; i++)
    {
        StackPop(&stk, &x);
    }
    StackDump(&stk);
    StackPop(&stk, &x);
    StackDump(&stk);


    return 0;
}



