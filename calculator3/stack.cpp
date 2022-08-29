#include "stack.h"
#include<bits/stdc++.h>
using namespace std;

//************运算符栈函数************

Status InitStack_op(Stack_op &S) {
    //初始化运算符栈S
    S.base = (QChar*)malloc(STACK_INIT_SIZE*sizeof(QChar));
    if(!S.base) exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status Push_op(Stack_op &S, QChar e) {
    //插入运算符e为新的栈顶元素
    if(S.top-S.base>=S.stacksize)
    {
        S.base = (QChar*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(QChar));
        if(!S.base) exit(OVERFLOW);
        S.top = S.base+S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}

Status Pop_op(Stack_op &S, QChar &e) {
    //栈S非空，删除S的栈顶元素并用e返回其值
    if(S.top==S.base) return ERROR;
    e = *--S.top;
    return OK;
}

Status GetTop_op(Stack_op S, QChar &e) {
    //栈S非空，用e返回S的栈顶元素
    if(S.top==S.base) return ERROR;
    e=*(S.top-1);
    return OK;
}

bool StackEmpty_op(Stack_op S) {
    //若运算符栈S为空栈，则返回TRUE，否则FALSE
    if(S.top==S.base) return TRUE;
    return FALSE;
}

Status DestroyStack_op(Stack_op &S) {
    //销毁运算符栈S
    free(S.base);
    S.base = NULL;
    return OK;
}

Status ClearStack_op(Stack_op &S) {
    //清空运算符栈S
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

//************操作数栈函数************

Status InitStack_num(Stack_num &S) {
    //初始化操作数栈S
    S.base = (float*)malloc(STACK_INIT_SIZE*sizeof(float));
    if(!S.base) exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status Push_num(Stack_num &S,float e) {
    //插入操作数e为新的栈顶元素
    if(S.top-S.base>=S.stacksize)
    {
        S.base = (float*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(float));
        if(!S.base) exit(OVERFLOW);
        S.top = S.base+S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}

Status Pop_num(Stack_num &S, float &e) {
    //栈S非空，删除S的栈顶元素并用e返回其值
    if(S.top==S.base) return ERROR;
    e = *--S.top;
    return OK;
}

Status GetTop_num(Stack_num S, float &e) {
    //栈S非空，用e返回S的栈顶元素
    if(S.top==S.base) return ERROR;
    e = *(S.top-1);
    return OK;
}

bool StackEmpty_num(Stack_num S) {
    //若操作数栈S为空栈，则返回TRUE，否则FALSE
    if(S.top==S.base) return TRUE;
    return FALSE;
}

Status DestroyStack_num(Stack_num &S) {
    //销毁操作数栈S
    free(S.base);
    S.base = NULL;
    return OK;
}
Status ClearStack_num(Stack_num &S) {
    //清空操作数栈S
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

