//#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>

#define MVHS fprintf(stderr, "Mushroom Wizard Honey Sack\n") 

typedef double StackElem_t;

enum errc 
{
    ALLOC_ERROR = -5,
};

struct Stack_t
{
    StackElem_t* data;
    size_t size;
    size_t capacity;
    enum errc ErrCode;
};

const size_t REALLOC_COEF = 2;





int StackDtor(Stack_t* stk);
int StackPush(Stack_t* stk, StackElem_t elem);
int StackInit(Stack_t* stk, size_t InitCapacity);
void* wrecalloc(void* ptr, size_t num, size_t size);
int StackResize(Stack_t* stk, bool downSizeFlag);
int StackPop(Stack_t* stk, StackElem_t* elem);





int main()
{
    Stack_t stk = {};

    StackInit(&stk, 67);

    for(int i = 0; i < 65; i++)
    {
       
        StackPush(&stk, 69.69);
        //fprintf(stderr, "current size: %zu\n", stk.size);

    }

    fprintf(stderr, "%zu\n", stk.capacity);
    double x = 0;
    StackPop(&stk, &x);
    fprintf(stderr, "%zu\n", stk.size);

    MVHS;

    free(stk.data);

    MVHS;

    return 0;
}


int StackDtor(Stack_t* stk)
{
    memset(stk->data, 0, sizeof(StackElem_t)*stk->capacity);
    free(stk->data);
    return 0; 
}

int StackPush(Stack_t* stk, StackElem_t elem)
{
    if(stk->size >= stk->capacity)
    {
        if(StackResize(stk, false) != 0)
        {
            assert(0);
            return ALLOC_ERROR;
        }
    }
    
    stk->data[stk->size] = elem;
    stk->size++;

    return 0;
}


int StackPop(Stack_t* stk, StackElem_t* elem)
{
    if(stk->size <= stk->capacity/4)
    {
        if(StackResize(stk, true) != 0)
        {
            assert(0);
            return ALLOC_ERROR;
        }
    }
    
    *elem = stk->data[stk->size];
    stk->data[stk->size] = 0;
    stk->size--;

    return 0;
}


int StackResize(Stack_t* stk, bool downSizeFlag)
{
    if(downSizeFlag)
    {
        if(wrecalloc(stk, stk->capacity/REALLOC_COEF, sizeof(StackElem_t)) == NULL)
        {
            perror("Wrecalloc:");
            free(stk->data);
            assert(0);
            
            return ALLOC_ERROR;
        }
        stk->capacity /= REALLOC_COEF;
        return 0;
    }

    else
    {
        if(wrecalloc(stk->data, stk->capacity*REALLOC_COEF, sizeof(StackElem_t)) == NULL)
        {
            perror("Wrecalloc:");
            free(stk->data);
            assert(0);
            
            return ALLOC_ERROR;
        }
        fprintf(stderr, "REALL DONE\n");
        stk->capacity *= REALLOC_COEF;
        return 0;
    } 
    return 0;
}


int StackInit(Stack_t* stk, size_t InitCapacity)
{
    if((stk->data = (double*)calloc(16, sizeof(double))) == NULL)
    {
        fprintf(stderr, "Dynamic Memory dead\n");
        assert(0);
        return ALLOC_ERROR; 
    }
    stk->size = 0;
    stk->capacity = InitCapacity;
    return 0;
}

void* wrecalloc(void* ptr, size_t num, size_t size)
{
    return realloc(ptr, num*size);//memset(, 0, num*size);
} 
