/*#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>z*/
#include <inttypes.h>
#include "Stack.h"


int Verificator(MyStack_t * stk)
{
    int errorNum = 0;

    if (stk <= 0)
    {
        printf("    -Incorrect stack pointer. Verification interrupted\n");
        errorNum += 1;
        return errorNum;
    }

    if ((*stk).capacity <= 0)
    {
        printf("    -Capacity <= 0\n");
        errorNum += 1;
    }

    if ((*stk).ssize < 0)
    {
        printf("    -Size < 0\n");
        errorNum += 1;
    }

    if ((*stk).ssize > (*stk).capacity)
    {
        printf("    -Size > capacity\n");
    }

    if ((*stk).birb1 != FIRST_CANARY)
    {
        printf("    -First canary is dead\n");
        errorNum += 1;
    }

    if ((*stk).birb2 != SECOND_CANARY)
    {
        printf("    -Second canary is dead\n");
        errorNum += 1;
    }

    if (errorNum)
    {
        StackDump(stk, __LINE__);
    }
    else
    {
        printf("Stack is OK\n");
        StackDump(stk, __LINE__);
    }

    return errorNum;
}


int StackCtor(MyStack_t * stk)
{
    printf("Started construction\n");

    (*stk).data = (int*)calloc(START_CAPASITY, sizeof(int)) + 2;

    if ((*stk).data == NULL)
    {
        return 1;
    }

    (*stk).birb1 = FIRST_CANARY;
    (*stk).ssize = 0;
    (*stk).capacity = START_CAPASITY;
    (*stk).realCapacity = START_CAPASITY + 4;
    (*stk).birb2 = SECOND_CANARY;
    *(uint64_t*)((*stk).data - 2) = FIRST_CANARY;
    *(uint64_t*)((*stk).data) = SECOND_CANARY;

    for (int i = 2; i < (*stk).capacity; i++)
    {
        (*stk).data[i] = POISON_VALUE;
    }
    //memset((*stk).data, POISON_VALUE, (*stk).capacity * sizeof(int));

    Verificator(stk);

    return 0;

}


void StackDtor(MyStack_t * stk)
{
    memset((*stk).data - 2, 0, (*stk).realCapacity * sizeof(int));
    memset(stk, 0, sizeof(int));
}


void StackDump(MyStack_t * stk, size_t line)
{
    /*printf("\nCalled from %d\n"
           "MyStack_t [%p]\n"
           "{\n"
           "    canary1 = %lX\n"
           "    size = %d\n"
           "    capacity = %d\n"
           "    realCapacity = %d\n"
           "    data [%p]:\n"
           "    {\n",
           line, stk, (*stk).birb1, (*stk).ssize, (*stk).capacity, (*stk).realCapacity, (*stk).data); */
    printf("\n\nRT_RT_RT_RT_RT_RT_RT_RT_RT_RT_RT_RT_RT_RT_RT_RT\n");

    printf("Called from %d\n", line);
    printf("MyStack_t [%p]\n", stk);
    printf("{\n");
    printf("    canary1 = %lX\n", (*stk).birb1);
    printf("    size = %d\n", (*stk).ssize);
    printf("    capacity = %d\n", (*stk).capacity);
    printf("    realCapacity = %d\n", (*stk).realCapacity);
    printf("    data [%p]:\n", (*stk).data);
    printf("    {\n");
    printf("        canary3 = %lX\n", *(uint64_t*)((*stk).data - 2));

    for (int i = 0; i < (*stk).ssize; i++)
    {
        printf("        *[%d] = %X", i, (*stk).data[i]);

        if ((*stk).data[i] == POISON_VALUE)
        {
            printf(" (poison value)");
        }

        printf("\n");
    }

    printf("        canary4 = %lX\n", *(uint64_t*)((*stk).data + (*stk).ssize));

    for (int i = (*stk).ssize + 2; i < (*stk).realCapacity - 2; i++)
    {
        printf("        *[%d] = %X", i, (*stk).data[i]);

        if ((*stk).data[i] == POISON_VALUE)
        {
            printf(" (poison value)");
        }

        printf("\n");
    }

    printf("    }\n"
           "    canary2 = %lX\n"
           "}\n", (*stk).birb2);

    printf("RT_RT_RT_RT_RT_RT_RT_RT_RT_RT_RT_RT_RT_RT_RT_RT\n\n\n");


}


int StackPush(int pushedElem, MyStack_t * stk)
{
    if (Verificator(stk))
    {
        printf("Push canceled");
        return 1;
    }

    if ((*stk).ssize > (*stk).capacity)
    {
        StackExpand(stk);
    }

    *(uint64_t*)((*stk).data + (*stk).ssize + 1) =
        *(uint64_t*)((*stk).data + (*stk).ssize);

    ((*stk).data)[(*stk).ssize] = pushedElem;
    (*stk).ssize += 1;

    return 0;
}


int StackPop(MyStack_t * stk)
{
    if (Verificator(stk))
    {
        printf("Pop canceled");
        return NAN;
    }

    if ((*stk).ssize == 0)
    {
        printf("Pop failed because stack is empty\n");
        return NAN;
    }

    (*stk).ssize -= 1;
    int retVal = (*stk).data[(*stk).ssize];
    *(uint64_t*)((*stk).data + (*stk).ssize) = *(uint64_t*)((*stk).data + (*stk).ssize + 1);

    if ((*stk).ssize * 4 <= (*stk).capacity)
    {
        StackCut(stk);
    }

    return retVal;
}


void StackCut(MyStack_t * stk)
{
    for (int i = (*stk).ssize + 2; i < (*stk).realCapacity - 2; i++)
    {
        (*stk).data[i] = POISON_VALUE;
    }

    (*stk).data = (int*)realloc((*stk).data - 2, ((*stk).realCapacity - (*stk).capacity / 2) * sizeof(int)) + 2;

    (*stk).realCapacity -= (*stk).capacity / 2;
    (*stk).capacity /= 2;
}


int StackExpand(MyStack_t * stk)
{
    (*stk).data = (int*)realloc((*stk).data - 2, ((*stk).realCapacity + (*stk).capacity) * sizeof(int)) + 2;

    if ((*stk).data == NULL)
    {
        printf("Failed to realloc.\n");
        //Dump
        return 1;
    }

    (*stk).realCapacity += (*stk).capacity;
    (*stk).capacity *= 2;

    return 0;
}


uint64_t Hahash(MyStack_t * stk)
{
    uint64_t newHash = 0;
    (*stk).hahash = 0;

    for (int i = 0; i < sizeof(MyStack_t); i++)
    {
        newHash = newHash * 33 + *(char*)(stk + i);
    }

    for (int i = 0; i < (*stk).capacity; i++)
    {
        newHash = newHash * 33 + *(char*)((*stk).data + i);
    }

    (*stk).hahash = newHash;

    return newHash;
}

