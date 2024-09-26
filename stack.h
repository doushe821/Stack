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
    ALLOC_ERROR = -5,
    DESTRUCTOR_ERROR,
    FILE_CREATION_ERROR,
    NO_ERRORS = 0,
};

struct Stack_t
{
    StackElem_t* data;
    size_t size;
    size_t capacity;
    enum errc ErrCode;
};

const size_t REALLOC_COEF = 2;


#ifndef STACK_DUMP_DEFINED
#define StackDump(Stack) doStackDump(&Stack, #Stack, __FILE__, __func__, __LINE__)
#endif

       
#define MWHS fprintf(stderr, "Mushroom Wizard Honey Sack\n")    
int StackDtor(Stack_t* stk);
int StackPush(Stack_t* stk, StackElem_t elem);
int StackInit(Stack_t* stk, size_t InitCapacity);
int doStackDump(Stack_t* stk, const char* StackName, const char* file, const char* func, int line);
void* wrecalloc(void* ptr, size_t num, size_t size);
int StackResize(Stack_t* stk, bool downSizeFlag);
int StackPop(Stack_t* stk, StackElem_t* elem);




#endif