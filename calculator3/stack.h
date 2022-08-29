#ifndef STACK_H
#define STACK_H

#include "define.h"
#include<QString>
#include<bits/stdc++.h>
using namespace std;

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct {    //定义结构体运算符栈
    QChar *base;
    QChar *top;
    int stacksize;
}Stack_op;

typedef struct {    //定义结构体操作数栈
    float *base;
    float *top;
    int stacksize;
}Stack_num;

Status InitStack_op(Stack_op &S);
Status Push_op(Stack_op &S, QChar e);
Status Pop_op(Stack_op &S, QChar &e);
Status GetTop_op(Stack_op S, QChar &e);
bool StackEmpty_op(Stack_op S);
Status DestroyStack_op(Stack_op &S);
Status ClearStack_op(Stack_op &S);

Status InitStack_num(Stack_num &S);
Status Push_num(Stack_num &S, float e);
Status Pop_num(Stack_num &S, float &e);
Status GetTop_num(Stack_num S, float &e);
bool StackEmpty_num(Stack_num S);
Status DestroyStack_num(Stack_num &S);
Status ClearStack_num(Stack_num &S);

#endif // STACK_H
