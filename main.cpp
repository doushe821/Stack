#include "stack.h"
#include "StackDB.h"


int main()
{


    Stack_t stk = {};

    StackInit(&stk, 8);
    for(int i = 0; i < 198; i++)
    {
        StackPush(&stk, 1611);
    }
    StackElem_t x = 0;
    for(int i  = 0; i < 128; i++)
    {
        StackPop(&stk, &x);
    }
    StackPop(&stk, &x);


    return 0;
}



