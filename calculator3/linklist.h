#ifndef LINKLIST_H
#define LINKLIST_H

#include"define.h"
#include<QString>
#include<bits/stdc++.h>
using namespace std;

typedef struct{
    float coef;
    int expn;
}term,ElemType_p;

typedef struct LNode{      //结点类型
    ElemType_p data;
    struct LNode *next;
}LNode,*Link;

typedef struct{            //链表类型
    Link head,tail;
    int len;
}LinkList;

Status MakeNode(Link &p, ElemType_p e);
void FreeNode(Link &p);
Status InitList(LinkList &L);
Status DestroyList(LinkList &L);
Status ClearList(LinkList &L);
Status AppendList(LinkList &L, Link s);
Link PriorPos(LinkList L, Link p);
Status InsBefore(LinkList &L, Link &p, Link s);
Status InsAfter(LinkList &L, Link &p, Link s);
Status DeleteList(LinkList &L, Link &p);
Status PutList(LinkList &L, ElemType_p e);
QString output_pl(LinkList L);
int cmp_expn(term a, term b);
QString Add_pl(LinkList La, LinkList Lb, LinkList &Lc);
QString Substract_pl(LinkList La, LinkList Lb, LinkList &Lc);
QString Multiply_pl(LinkList La, LinkList Lb, LinkList &Lc);
QString Deri_pl(LinkList La, LinkList &Lb);

#endif // LINKLIST_H
