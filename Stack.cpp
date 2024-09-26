#include "stack.h"



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
        if(wrecalloc(stk->data, stk->capacity/REALLOC_COEF, sizeof(StackElem_t)) == 0)
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
        if(wrecalloc(stk->data, stk->capacity*REALLOC_COEF, sizeof(StackElem_t)) == 0)
        {
            perror("Wrecalloc:");
            free(stk->data);
            assert(0);
            
            return ALLOC_ERROR;
        }

        stk->capacity *= REALLOC_COEF;
        return 0;
    } 
    return 0;
}


int StackInit(Stack_t* stk, size_t InitCapacity)
{
    if((stk->data = (double*)calloc(InitCapacity, sizeof(double))) == NULL)
    {
        fprintf(stderr, "Dynamic Memory dead\n");
        assert(0);
        return ALLOC_ERROR; 
    }
    stk->size = 0;
    stk->capacity = InitCapacity;
    return 0;
}
                                                                      
int doStackDump(Stack_t* stk, const char* StackName, const char* file, const char* func, int line)
{
    MWHS;
    FILE* log = fopen("log.txt", "w+b");
    if(log == NULL)
    {
        MWHS;
        fclose(log);
        return FILE_CREATION_ERROR;
    }

    fprintf(log, 
    "########################## STACK INFO ##########################\n"
    "## STACK NAME     : %s\n"
    "## CALLER FILE    : %s\n"
    "## CALLER FUNCTION: %s\n"
    "## LINE          = %d\n"
    "## STACK ERRORS  = %d\n"
    "## STACK SIZE    = %zu\n"
    "## STACK CAPACIY = %zu\n"
    "## STACK DATA:\n"
    , StackName, file, func, line, stk->ErrCode, stk->size, stk->capacity);

    for(int i = 0; i < stk->size; i++)
    {
        fprintf(log, "[%lf], ", stk->data[i]);
        if((i + 1) % 5 == 0)
        {
            fprintf(log, "\n");
        }
    }

    fclose(log);

    return 0;
}

void* wrecalloc(void* ptr, size_t num, size_t size)
{
    void* tptr = NULL;
    tptr = realloc(ptr, num*size);

    if(tptr == NULL)
    {
        free(ptr);
        return NULL;
    }

    return tptr;//memset(, 0, num*size);
} 