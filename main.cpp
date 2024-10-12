#include <stdio.h>
#include "Stack.h"


int main()
{
    MyStack_t stk;
    StackCtor(&stk);

    //Verificator(&stk);

    StackPush(1, &stk);
    StackPush(2, &stk);
    StackPush(3, &stk);
    StackPush(4, &stk);

    printf("pop %d\n", StackPop(&stk));

    StackPush(5, &stk);
    StackPush(6, &stk);

    //StackDump(&stk, __LINE__);

    Verificator(&stk);

    printf("pop %d\n", StackPop(&stk));
    printf("pop %d\n", StackPop(&stk));
    printf("pop %d\n", StackPop(&stk));
    printf("pop %d\n", StackPop(&stk));
    printf("pop %d\n", StackPop(&stk));
    printf("pop %d\n", StackPop(&stk));
}
