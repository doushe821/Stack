#include "stack.h"

int doStackInit(Stack_t* stk, size_t InitCapacity)
{
    if((stk->data = (double*)calloc(InitCapacity, sizeof(double))) == NULL)
    {
        fprintf(stderr, "Dynamic Memory dead\n");
        stk->Error = ALLOC_ERROR;
        return ALLOC_ERROR; 
    }
    stk->size = 0;
    stk->capacity = InitCapacity;
    return NO_ERRORS;
}
                   
int doStackDtor(Stack_t* stk)
{
    void* ptr = memset(stk->data, 0, sizeof(StackElem_t)*stk->capacity);

    if(ptr == NULL)
    {
        stk->Error = MEMSET_FAILURE;
        free(stk->data);
        return MEMSET_FAILURE;
    }

    free(stk->data);

    return NO_ERRORS; 
}

int doStackPush(Stack_t* stk, StackElem_t elem)
{
    if(stk->size >= stk->capacity)
    {
        if(doStackResize(stk, false) != 0)
        {
            stk->Error = ALLOC_ERROR;
            free(stk->data);
            return ALLOC_ERROR;
        }
    }
    
    stk->data[stk->size] = elem;
    stk->size++;

    return NO_ERRORS;
}


int doStackPop(Stack_t* stk, StackElem_t* elem)
{
    if(stk->size <= 0)
    {
        return NO_MORE_ELEMENTS;
    }
    if(stk->size <= stk->capacity/4)
    {
        
        if(doStackResize(stk, true) != 0)
        {
            stk->Error = ALLOC_ERROR;
            free(stk->data);
            return ALLOC_ERROR;
        }
    }
    
    *elem = stk->data[stk->size];
    stk->data[stk->size] = 0;
    stk->size--;

    return NO_ERRORS;
}

int doStackResize(Stack_t* stk, bool downSizeFlag)
{
    if(downSizeFlag)
    {
        if((stk->data = (StackElem_t*)wrecalloc(stk->data, stk->capacity/REALLOC_COEF, sizeof(StackElem_t))) == 0)
        {
            stk->Error = ALLOC_ERROR;
            free(stk->data);
            
            return ALLOC_ERROR;
        }
        stk->capacity /= REALLOC_COEF;

        return NO_ERRORS;
    }

    else
    {
        if((stk->data = (StackElem_t*)wrecalloc(stk->data, stk->capacity*REALLOC_COEF, sizeof(StackElem_t)))== 0)
        {
            stk->Error = ALLOC_ERROR;
            free(stk->data);
            
            return ALLOC_ERROR;
        }

        stk->capacity *= REALLOC_COEF;

        return NO_ERRORS;
    } 
    return NO_ERRORS;
}

void* wrecalloc(void* ptr, size_t num, size_t size)
{
    void* tptr = calloc(num, size);
    if(tptr == NULL)
    {
        free(ptr);
        free(tptr);
        return NULL;
    }

    memcpy(tptr, ptr, num*size);
    free(ptr);
    return tptr;
} 
                                                           
int doStackDump(Stack_t* stk, const char* file, const char* func, int line)
{
    FILE* log = fopen("log.txt", "a+b");
    if(log == NULL)
    {
        stk->Error = FILE_CREATION_ERROR;
        fclose(log);
        return FILE_CREATION_ERROR;
    }

    fprintf(log, 
    "########################## STACK INFO ##########################\n"
    "## CALLER FILE    : %s\n"
    "## CALLER FUNCTION: %s\n"
    "## LINE          = %d\n"
    "## STACK ERRORS  = %d\n"
    "## STACK SIZE    = %zu\n"
    "## STACK CAPACIY = %zu\n"
    "## STACK DATA:\n"
    , file, func, line, stk->Error, stk->size, stk->capacity);

    for(int i = 0; i < stk->size; i++)
    {
        fprintf(log, "[%lf], ", stk->data[i]);
        if((i + 1) % 5 == 0)
        {
            fprintf(log, "\n");
        }
    }
    fprintf(log, "\n\n\n");

    fclose(log);

    return NO_ERRORS;
}

void errParse(int e)
{
    switch(e)
    {
        case ALLOC_ERROR:
        {
            fprintf(stderr, "Cannot allocate memory.\n");
            break;
        }

        case DESTRUCTOR_ERROR:
        {
            fprintf(stderr, "Could not destruct stack, closing program.");
            break;
        }

        case FILE_CREATION_ERROR:
        {
            fprintf(stderr, "Could not open existing or create new log.txt file.");
            break;
        }

        case MEMSET_FAILURE:
        {
            fprintf(stderr, "Could not initialise allocated memory.");
            break;
        }

        case NO_MORE_ELEMENTS:
        {
            fprintf(stderr, "You tried to grab an element from an empty stack.");
            break;
        }

        default:
        {
            fprintf(stderr, "An undefined error appeared. Please, make a report to make program better.");
        }
    }
}