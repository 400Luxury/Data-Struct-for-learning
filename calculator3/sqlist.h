#ifndef SQLIST_H
#define SQLIST_H

#include "define.h"
#include<QString>
#include<bits/stdc++.h>
using namespace std;

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define LIST_INIT_NUM 20

typedef float ElemType;
typedef struct{         //顺序表结构的定义
    ElemType *elem;     //存储空间基址
    int length;         //当前长度
    int listsize;       //当前分配的存储容量(以sizeof(ELemType)为单位)
}SqList;

Status InitList_Sq(SqList &L);
Status DestroyList_Sq(SqList &L);
Status ClearList_Sq(SqList &L);
Status GetElem(SqList L, int i, ElemType &e);
Status PutElem(SqList &L, int i, ElemType e);
QString output_v(SqList &L);
QString output_p(SqList &L);
QString Add_v(SqList La, SqList Lb, SqList &Lc);
QString Substract_v(SqList La, SqList Lb, SqList &Lc);
float Cosine_Sq(SqList La, SqList Lb);
QString Add_p(SqList La, SqList Lb, SqList &Lc);
QString Substract_p(SqList La, SqList Lb, SqList &Lc);
QString Multiply_p(SqList La, SqList Lb, SqList &Lc);
QString Deri_p(SqList La, SqList Lb);

#endif // SQLIST_H
