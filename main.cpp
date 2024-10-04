#include "stack.h"
#include "StackDB.h"



int main()
{

    #ifndef NDEBUG
    FILE* clean = fopen("log.txt", "w+b");
    fclose(clean);
    #endif

    Stack_t stk = {};

    stk.elSize = 4;

    STACK_INIT(&stk, 12800);

    //StackDump(&stk);
    int y = 3333; 

    StackPush(&stk, &y);
  
    //*(int*)((char*)stk.data + 1*stk.elSize) = 69;
    
    //StackPop(&stk, &y);tackPush(&stk, &y); StackPush(&stk, &y);   StackPush(&stk, &y); StackPush(&stk, &y); StackPush(&stk, &y); StackPush(&stk, &y); StackPush(&stk, &y); StackPush(&stk, &y); StackPush(&stk, &y); StackPush(&stk, &y); StackPush(&stk, &y);
    //fprintf(stderr, "%d\n", *((int*)((char*)stk.data)));
    for(size_t i = 0; i < 100; i++)
    {
      StackPush(&stk, &y);
    }

    VoidIntDump(&stk);

    //StackDump(&stk);
    StackDtor(&stk);
    return 0;
}

