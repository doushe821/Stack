#include "stack.h"
#include "StackDB.h"

int StackInit(Stack_t* stk, size_t InitCapacity)
{

    if(stk == NULL)
    {
        return STACK_PTR_IS_NULL;
    }

    if((stk->data = (double*)calloc(InitCapacity + 3, sizeof(double))) == NULL)
    {
        fprintf(stderr, "Dynamic Memory dead\n");
        stk->Error = ALLOC_ERROR;
        return ALLOC_ERROR; 
    }

    stk->size = 0;
    stk->capacity = InitCapacity;
    
    return NO_ERRORS;
}
                   
int StackDtor(Stack_t* stk)
{
    STACK_ASSERT(stk);
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

int StackPush(Stack_t* stk, StackElem_t elem)
{
    STACK_ASSERT(stk);
    if(stk->size >= stk->capacity)
    {
        if(StackResize(stk, false) != 0)
        {
            stk->Error = ALLOC_ERROR;
            free(stk->data);
            return ALLOC_ERROR;
        }
    }
    
    stk->data[stk->size] = elem;
    stk->size++;

    STACK_ASSERT(stk);

    return NO_ERRORS;
}


int StackPop(Stack_t* stk, StackElem_t* elem)
{
    STACK_ASSERT(stk);

    if(stk->size <= 0)
    {
        return STACK_UNDERFLOW;
    }
    if(stk->size <= stk->capacity/4)
    {
        
        if(StackResize(stk, true) != 0)
        {
            stk->Error = ALLOC_ERROR;
            free(stk->data);
            return ALLOC_ERROR;
        }
    }
    
    *elem = stk->data[stk->size];
    stk->data[stk->size] = NAN;
    stk->size--;

    STACK_ASSERT(stk);
    return NO_ERRORS;
}

int StackResize(Stack_t* stk, bool downSizeFlag)
{
    STACK_ASSERT(stk);

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
    STACK_ASSERT(stk);
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

        case STACK_UNDERFLOW:
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