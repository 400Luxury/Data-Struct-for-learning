#include "linklist.h"
#include<bits/stdc++.h>
using namespace std;

Status MakeNode(Link &p, ElemType_p e){
    //分配由p指向值为e的结点
    p = (LNode*)malloc(sizeof(LNode));
    if (!p) exit(OVERFLOW);
    p->data = e;
    p->next = NULL;
    return OK;
}

void FreeNode(Link &p){
    //释放p所指结点
    free(p);
    p = NULL;
}

Status InitList(LinkList &L){
    //构造一个空的线性链表L
    L.head = (LNode*)malloc(sizeof(LNode));
    if (!L.head) exit(OVERFLOW);
    L.tail = L.head;
    L.head->next = NULL;
    L.len = 0;
    return OK;
}

Status DestroyList(LinkList &L){
    //销毁线性链表L，L不再存在
    Link p = L.head;
    while (p)
    {
        Link q = p;
        p = p->next;
        free(q);
    }
    L.tail = L.head = NULL;
    return OK;
}

Status ClearList(LinkList &L){
    //将线性链表L重置为空表，并释放原链表的结点空间。
    Link p = L.head->next;
    while (p)
    {
        Link q = p;
        p = p->next;
        free(q);
    }
    L.tail = L.head;
    L.len = 0;
    L.head->next = NULL;
    return OK;
}

Status AppendList(LinkList &L, Link s){
    //将指针s所指的一串结点链接在线性链表L的最后一个结点
    L.tail->next = s;
    while (L.tail->next)
    {
        L.tail = L.tail->next;
        L.len++;
    }
    return OK;
}

Link PriorPos(LinkList L, Link p){
    //返回p所指的直接前驱的位置，若无则返回NULL
    Link q = L.head;
    while (q->next != p)
    {
        q = q->next;
    }
    return q;
}

Status InsBefore(LinkList &L, Link &p, Link s){
    //已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之前，并修改指针p指向新插入的结点
    Link q = PriorPos(L,p);
    s->next = p;
    q->next = s;
    p = s;
    L.len++;
    return OK;
}

Status InsAfter(LinkList &L, Link &p, Link s){
    //已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之后，并修改指针p指向新插入的结点
    s->next = p->next;
    p->next = s;
    p = s;
    L.len++;
    return OK;
}

Status DeleteList(LinkList &L, Link &p){
    //删除链表L中p所指结点
    Link q = PriorPos(L,p);
    q->next = p->next;
    FreeNode(p);
    L.len--;
    return OK;
}

Status PutList(LinkList &L, ElemType_p e){
    //将新的一项按次数加入有序链表L
    Link p = L.head->next;
    Link s;
    MakeNode(s,e);

    while(p)
    {
        if(p->data.expn > e.expn)
        {
            InsBefore(L, p, s);
            return OK;
        }

        else if(p->data.expn == e.expn)
        {
            p->data.coef += e.coef;
            if(fabs(p->data.coef) <= 1e-6)
            {
                DeleteList(L,p);
            }
            return OK;
        }

        p=p->next;
    }

    AppendList(L,s);
    return OK;
}

QString output_pl(LinkList L){
    //遍历链表L,输出多项式值
    if (L.len==0) {  //多项式为0时
        return "0";
    }

    QString s = "";
    Link p = L.head->next;
    term headterm = p->data;

    if (headterm.expn==0) {
        s.append(QString("%1").arg(headterm.coef));
        p = p->next;
    }

    while(p) {
        term e = p->data;
        if(e.coef>0 && s!="") s.append("+"+QString("%1").arg(e.coef));
        else s.append(QString("%1").arg(e.coef));
        s.append("x^"+QString::number(e.expn));
        p = p->next;
    }

    return s;
}

int cmp_expn(term a, term b){
    //依a的指数值<(or=)(or>)b的指数值，分别返回-1、0和+1
    return a.expn>b.expn ? 1 : a.expn<b.expn ? -1 : 0;
}

QString Add_pl(LinkList La, LinkList Lb, LinkList &Lc){
    //多项式La与Lb相加得到Lc
    Link pa = La.head->next; Link pb = Lb.head->next;
    Link q = NULL;
    while (pa && pb)
    {
        term a = pa->data;
        term b = pb->data;
        ElemType_p sum;
        switch (cmp_expn(a,b))
        {
        case -1:
            sum.coef = a.coef;
            sum.expn = a.expn;
            MakeNode(q,sum);
            AppendList(Lc,q);
            q = NULL;
            pa = pa->next;
            break;

        case 0:
            sum.coef = a.coef + b.coef;
            if (fabs(sum.coef) > 1e-6) {
                sum.expn = a.expn;
                MakeNode(q,sum);
                AppendList(Lc,q);
                q = NULL;
            }
            pa = pa->next; pb = pb->next;
            break;

        case 1:
            sum.coef = b.coef;
            sum.expn = b.expn;
            MakeNode(q,sum);
            AppendList(Lc,q);
            q = NULL;
            pb = pb->next;
            break;
        }
    }
    if(pa) AppendList(Lc,pa);
    if(pb) AppendList(Lc,pb);

    return output_pl(Lc);
}

QString Substract_pl(LinkList La, LinkList Lb, LinkList &Lc){
    //La与Lb相减，结果赋给Lc
    Link pa = La.head->next; Link pb = Lb.head->next;
    Link q = NULL;
    while (pa && pb)
    {
        term a = pa->data;
        term b = pb->data;
        ElemType_p differ;
        switch (cmp_expn(a,b))
        {
        case -1:
            differ.coef = a.coef;
            differ.expn = a.expn;
            MakeNode(q,differ);
            AppendList(Lc,q);
            q = NULL;
            pa = pa->next;
            break;

        case 0:
            differ.coef = a.coef - b.coef;
            if (fabs(differ.coef) > 1e-6) {
                differ.expn = a.expn;
                MakeNode(q,differ);
                AppendList(Lc,q);
                q = NULL;
            }
            pa = pa->next; pb = pb->next;
            break;

        case 1:
            differ.coef = -b.coef;
            differ.expn = b.expn;
            MakeNode(q,differ);
            AppendList(Lc,q);
            q = NULL;
            pb = pb->next;
            break;
        }
    }
    if(pa) AppendList(Lc,pa);
    if(pb) AppendList(Lc,pb);
    while (pb)
    {
        pb->data.coef = -pb->data.coef;
        pb = pb->next;
    }

    return output_pl(Lc);
}

QString Multiply_pl(LinkList La, LinkList Lb, LinkList &Lc){
    //多项式La与Lb相乘得到Lc
    ElemType_p e;
    for(Link pa=La.head->next; pa; pa=pa->next) {
        for(Link pb=Lb.head->next; pb; pb=pb->next) {
            e.coef = pa->data.coef * pb->data.coef;
            e.expn = pa->data.expn + pb->data.expn;
            PutList(Lc,e);
        }
    }
    return output_pl(Lc);
}

QString Deri_pl(LinkList La, LinkList &Lb){
    //多项式La与Lb相乘得到Lc
    ElemType_p e;
    for(Link pa=La.head->next; pa; pa=pa->next) {
        if(!pa->data.expn) continue;
        e.coef = pa->data.coef * pa->data.expn;
        e.expn = pa->data.expn-1;
        PutList(Lb,e);
    }
    return output_pl(Lb);
}
