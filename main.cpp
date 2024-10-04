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

    STACK_INIT(&stk, 8);

    //StackDump(&stk);
    int y = 3333; 

    StackPush(&stk, &y);
  
    VoidIntDump(&stk); 
    
    StackPush(&stk, &y); StackPush(&stk, &y); *(int*)((char*)stk.data + 1*stk.elSize) = 69;  StackPush(&stk, &y); StackPush(&stk, &y); StackPush(&stk, &y); StackPush(&stk, &y); StackPush(&stk, &y); StackPush(&stk, &y); StackPush(&stk, &y); StackPush(&stk, &y); StackPush(&stk, &y);
    VoidIntDump(&stk);
    //StackPop(&stk, &y);
    //fprintf(stderr, "%d\n", *((int*)((char*)stk.data)));


    int x = 9;
    int* xptr = &x;
    
      StackPop(&stk, &x);  StackPop(&stk, &x);  StackPop(&stk, &x);  StackPop(&stk, &x);  StackPop(&stk, &x);  StackPop(&stk, &x);  StackPop(&stk, &x);  StackPop(&stk, &x);  StackPop(&stk, &x);  StackPop(&stk, &x);  StackPop(&stk, &x);  StackPop(&stk, &x);
    
    //VoidIntDump(&stk);    
    /*void* killerptr = ((char*)stk.data - 5*stk.elSize);
    for(int i = 0; i < 11; i++)
    {
        *(int*)((char*)killerptr + i*stk.elSize) = 7;
    }    */ //TORTURE ROOM

    VoidIntDump(&stk);

    //StackDump(&stk);
    StackDtor(&stk);
    return 0;
}

