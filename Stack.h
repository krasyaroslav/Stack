#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define POISON_VALUE 0xDED
#define FIRST_CANARY 0xDED15BAD
#define SECOND_CANARY 0xFEEDDEDA
#define START_CAPASITY 8

#ifndef __Stack__
#define __Stack__

struct MyStack_t
{
     uint64_t birb1;
     size_t ssize;
     size_t capacity;
     size_t realCapacity;
     uint64_t hahash;
     int * data;
     uint64_t birb2;
};


int Verificator(MyStack_t * stk);
int StackCtor(MyStack_t * stk);
void StackDtor(MyStack_t * stk);
void StackDump(MyStack_t * stk, size_t line);
int StackPush(int pushedElem, MyStack_t * stk);
int StackPop(MyStack_t * stk);
void StackCut(MyStack_t * stk);
int StackExpand(MyStack_t * stk);


#endif
