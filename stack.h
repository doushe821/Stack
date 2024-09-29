#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <math.h>


typedef double StackElem_t;

enum errc
{
    UNDEFINED_ERROR = 2,
    ALLOC_ERROR = 4,
    DESTRUCTOR_ERROR = 8,
    FILE_CREATION_ERROR = 16,
    MEMSET_FAILURE = 32,
    STACK_UNDERFLOW = 64,
    STACK_PTR_IS_NULL = 128,
    DATA_PTR_IS_NULL = 256,
    STACK_OVERFLOW = 512,
    NO_ERRORS = 0,
};

struct Stack_t
{
    #ifndef NDEBUG
    const char* stkName;
    const char* file;
    const char* func;
    const int line;
    #endif
    StackElem_t* data;
    size_t size;
    size_t capacity;
    size_t Error;
};

const size_t REALLOC_COEF = 2; // USED WHILE REALLOCATING MEMORY, CHANGE IF NEEDED.


int StackDtor(Stack_t* stk);
int StackPush(Stack_t* stk, StackElem_t elem);
int StackInit(Stack_t* stk, size_t InitCapacity);
int StackResize(Stack_t* stk, bool downSizeFlag);
int StackPop(Stack_t* stk, StackElem_t* eslem);
void* wrecalloc(void* ptr, size_t num, size_t size);
void errParse(int e);

#endif