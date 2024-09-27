#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>


typedef double StackElem_t;

enum errc
{
    UNDEFINED_ERROR = -6,
    ALLOC_ERROR,
    DESTRUCTOR_ERROR,
    FILE_CREATION_ERROR,
    MEMSET_FAILURE,
    NO_MORE_ELEMENTS,
    NO_ERRORS = 0,
};

struct Stack_t
{
    StackElem_t* data;
    size_t size;
    size_t capacity;
    int Error;
};

const size_t REALLOC_COEF = 2; // USED WHILE REALLOCATING MEMORY, CHANGE IF NEEDED.


int doStackDtor(Stack_t* stk);
int doStackPush(Stack_t* stk, StackElem_t elem);
int doStackInit(Stack_t* stk, size_t InitCapacity);
int doStackDump(Stack_t* stk, const char* file, const char* func, int line);
int doStackResize(Stack_t* stk, bool downSizeFlag);
int doStackPop(Stack_t* stk, StackElem_t* elem);
void* wrecalloc(void* ptr, size_t num, size_t size);
void errParse(int e);


//// STACK FUNCTION MACROSES.
////

#ifndef STACK_DUMP_DEFINED
#define StackDump(Stack) if((Stack)->Error != NO_ERRORS) \
                         {int err = (Stack)->Error; errParse(err); exit(err);} else \
                         {doStackDump((Stack), __FILE__, __func__, __LINE__);}
#endif

#ifndef STACK_POP_INCLUDED
#define STACK_POP_INCLUDED
#define StackPop(Stack, x) if((Stack)->Error != NO_ERRORS) \
                           {int err = (Stack)->Error; errParse(err); exit(err);} else \
                           {doStackPop((Stack), (x));}
#endif

#ifndef STACK_PUSH_INCLUDED
#define STACK_PUSH_INCLUDED
#define StackPush(Stack, x) if((Stack)->Error != NO_ERRORS) \
                            {int err = (Stack)->Error; errParse(err); exit(err);} else \
                            {doStackPush((Stack), x);}
#endif

#ifndef STACK_INIT_INCLUDED
#define STACK_INIT_INCLUDED
#define StackInit(Stack, size) if((Stack)->Error != NO_ERRORS) \
                               {int err = (Stack)->Error; errParse(err); exit(err);} else \
                               {doStackInit((Stack), size);}
#endif

#ifndef STACK_RESIZE_INCLUDED
#define STACK_RESIZE_INCLUDED
#define StackResize(Stack, flag) if((Stack)->Error != NO_ERRORS) \
                                 {int err = (Stack)->Error; errParse(err); exit(err);} else \
                                 {doStackResize((Stack), flag);}
#endif

#ifndef STACK_DTOR_INCLUDED
#define STACK_DTOR_INCLUDED
#define StackDtor(Stack) if((Stack)->Error != NO_ERRORS) \
                         {int err = (Stack)->Error; errParse(err); exit(err);} else \
                         {doStackDtor(Stack);}
#endif

////
////

#endif