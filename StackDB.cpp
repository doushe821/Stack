#include "StackDB.h"

void StackAssert(Stack_t* stk, const char* stkName, const char* file, const char* func, int line)
{
    if(stk == NULL)
    {
        fprintf(stderr, "Stack pointer is NULL");
        assert(0);
    }

    if((stk->Error = StackError(stk)) != 0)
    {
        doStackDump(stk, stkName, file, func, line);
        assert(0);
    }
}

int StackError(Stack_t* stk)
{
    size_t errFlag = 0;
    if(stk == NULL)
    {
        fprintf(stderr, "Stack pointer is NULL\n");
        errFlag += STACK_PTR_IS_NULL;
    }

    if(stk->data == NULL)
    {
        fprintf(stderr, "Data pointer is NULL\n");
        errFlag += DATA_PTR_IS_NULL;
    }

    if(stk->size > stk->capacity)
    {
        fprintf(stderr, "Stack overflow\n");
        errFlag += STACK_OVERFLOW;
    }

    if(stk->size > UNLIKELY_STACK_SIZE)
    {
        fprintf(stderr, "Stack has negative size (stack underflow)\n");
        errFlag+=STACK_UNDERFLOW;
    }

    return errFlag;
}

int doStackDump(Stack_t* stk, const char* stkName, const char* file, const char* func, int line)
{
    FILE* log = fopen("log.txt", "w+b");
    if(log == NULL)
    {
        stk->Error = FILE_CREATION_ERROR;
        fclose(log);
        return FILE_CREATION_ERROR;
    }

    fprintf(log, 
    "########################## STACK INFO ##########################\n"
    "## CALLER STACK: %p\n"
    "## CALLER FILE    : %s\n"
    "## CALLER FUNCTION: %s\n"
    "## LINE          = %d\n"
    "## STACK ERRORS  = %zu\n"
    "## STACK SIZE    = %zu\n"
    "## STACK CAPACIY = %zu\n"
    "## STACK DATA: %p\n",
    stk, file, func, line, stk->Error, stk->size, stk->capacity, stk->data);

    for(int i = 0; i < stk->capacity; i++)
    {
        if(stk->data[i] != stk->data[i])
        {
            fprintf(log, "*[%lg] (POISON), ", stk->data[i]);
        }
        else
        {
            fprintf(log, "[%lg], ", stk->data[i]);
        }

        if((i + 1) % 5 == 0)
        {
            fprintf(log, " (%d)\n", i+1);
        }
    }
    fprintf(log, "\n\n\n");
    fprintf(log, 
    "## STACK ERRORS: ");

    size_t byte = 2;
    for(int i = 0; i < sizeof(size_t)*8; i++)
    {
        fprintf(log, "%zu", byte & stk->Error);
        byte *= 2;
    }
    fprintf(log, "\n\n\n");


    fclose(log);

    return NO_ERRORS;
}