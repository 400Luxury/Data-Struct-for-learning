#include "sqlist.h"
#include<bits/stdc++.h>
using namespace std;

Status InitList_Sq(SqList &L){
    //初始化顺序表L
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if (!L.elem) exit(OVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

Status DestroyList_Sq(SqList &L){
    //销毁顺序表L
    free(L.elem);
    L.elem=NULL;
    return OK;
}

Status ClearList_Sq(SqList &L)
{   //清空线性表L
    L.length=0;
    L.listsize=LIST_INIT_SIZE;
    return OK;
}

Status GetElem(SqList L, int i, ElemType &e){
    //返回L第i个维度的值
    if(i<0 || i>L.listsize) return ERROR;
    ElemType* p = L.elem;
    e = *(p+i-1);
    return OK;
}

Status PutElem(SqList &L, int i, ElemType e){
    //令L第i个维度的值为e
    if(i<0) return ERROR;
    if (i>L.listsize) {
        int oldsize = L.listsize;
        L.listsize += ((i-L.listsize)/LISTINCREMENT+1)*LISTINCREMENT;
        for (int j = oldsize+1; j<=L.listsize; j++) {
            PutElem(L, j, 0);
        }
    }
    ElemType* p = L.elem;
    *(p+i-1) = e;
    return OK;
}

QString output_v(SqList &L) {
    //输出向量值
    QString s="(";
    if (L.length == 0) s.append(")");
    else {
        for (int i=1; i<=L.length; i++) {
            float e;
            GetElem(L, i, e);
            s.append(QString("%1").arg(e));
            s.append(",");
        }
        s.chop(1);
        s.append(")");
    }
    return s;
}

QString Add_v(SqList La, SqList Lb, SqList &Lc){
    //La与Lb相加得到Lc
    QString s;
    ElemType a,b,c;

    if (La.length != Lb.length) {
        s = "维度不同，无法相加！";
    }
    else {
        Lc.length = La.length;
        for (int i = 1; i <=La.length; i++) {
            GetElem(La, i, a);
            GetElem(Lb, i, b);
            c = a + b;
            PutElem(Lc, i, c);
        }
        s = output_v(Lc);
    }
    return s;
}

QString Substract_v(SqList La, SqList Lb, SqList &Lc){
    //La与Lb相减得到Lc
    QString s;
    ElemType a,b,c;

    if (La.length != Lb.length) {
        s = "维度不同，无法相减！";
    }
    else {
        Lc.length = La.length;
        for (int i = 1; i <=La.length; i++) {
            GetElem(La, i, a);
            GetElem(Lb, i, b);
            c = a - b;
            PutElem(Lc, i, c);
        }
        s = output_v(Lc);
    }
    return s;
}

float Cosine_Sq(SqList La, SqList Lb) {
    //计算向量La和Lb之间的余弦值
    ElemType *pa = La.elem;
    ElemType *pb = Lb.elem;
    float fenzi = 0;
    float fenmu_a = 0;
    float fenmu_b = 0;
    for (int i = 1; i <=La.length; i++) {
        fenzi += (*(pa + i - 1)) * (*(pb + i - 1));
        fenmu_a += (*(pa + i - 1)) * (*(pa + i - 1));
        fenmu_b += (*(pb + i - 1)) * (*(pb + i - 1));
    }

    float cos;
    if(fenmu_a==0 || fenmu_b==0) {
        cos = 0;        //零向量与任何向量都垂直,余弦值为1
    }
    cos = fenzi / sqrt(fenmu_a * fenmu_b);
    return cos;
}

QString output_p(SqList &L) {
    //输出多项式值
    QString s = "";
    float e = 0;
    if (L.length==0) return "0";

    GetElem(L, 1, e);
    if(fabs(e)>1e-6) {
        s.append(QString("%1").arg(e));
    }

    for(int i=2; i<=L.length; i++) {
        GetElem(L, i, e);
        if(fabs(e)>1e-6) {
            if(e>0 && s!="") s.append("+"+QString("%1").arg(e));
            else s.append(QString("%1").arg(e));
            s.append("x^"+QString::number(i-1,10));
        }
    }
    return s;
}

QString Add_p(SqList La, SqList Lb, SqList &Lc){
    //多项式La与Lb相加得到Lc
    QString s;
    ElemType a,b,c;

    if (La.length != Lb.length) {
        if (La.length > Lb.length) {
            for (int j=Lb.length+1; j<=La.length; j++) {
                PutElem(Lb, j, 0);
            }
            Lb.length = La.length;
        }
        else {
            for (int j=La.length+1; j<=Lb.length; j++) {
                PutElem(La, j, 0);
            }
            La.length = Lb.length;
        }
    }

    Lc.length = La.length;
    for (int i = 1; i <=La.length; i++) {
        GetElem(La, i, a);
        GetElem(Lb, i, b);
        c = a + b;
        PutElem(Lc, i, c);
    }

    s = output_p(Lc);
    return s;
}

QString Substract_p(SqList La, SqList Lb, SqList &Lc){
    //多项式La与Lb相减得到Lc
    QString s;
    ElemType a,b,c;

    if (La.length != Lb.length) {
        if (La.length > Lb.length) {
            for (int j=Lb.length+1; j<=La.length; j++) {
                PutElem(Lb, j, 0);
            }
            Lb.length = La.length;
        }
        else {
            for (int j=La.length+1; j<=Lb.length; j++) {
                PutElem(La, j, 0);
            }
            La.length = Lb.length;
        }
    }

    Lc.length = La.length;
    for (int i = 1; i <=La.length; i++) {
        GetElem(La, i, a);
        GetElem(Lb, i, b);
        c = a - b;
        PutElem(Lc, i, c);
    }

    s = output_p(Lc);
    return s;
}

QString Multiply_p(SqList La, SqList Lb, SqList &Lc){
    //多项式La与Lb相乘得到Lc
    QString s;
    ElemType a,b,c,e;

    Lc.length = La.length + Lb.length -1;
    for (int i=1; i<=La.length; i++) {
        GetElem(La, i, a);
        for (int j=1; j<=Lb.length; j++) {
            GetElem(Lb, j, b);
            if (a && b) {
                GetElem(Lc, i+j-1, c);
                PutElem(Lc, i+j-1, c+a*b);
            }
        }
    }

    //使最高项不为0
    for (int i=Lc.length; i>1; i--) {
        GetElem(Lc, i, e);
        if(e) break;
    }

    s = output_p(Lc);
    return s;
}

QString Deri_p(SqList La, SqList Lb){
    //对多项式La求导得到Lb
    if (La.length==1) {
        Lb.length = 1;
        *Lb.elem = 0;
        return "0";
    }

    QString s;
    ElemType a;
    Lb.length = La.length - 1;
    for (int i=2; i<=La.length; i++) {
        GetElem(La, i, a);
        PutElem(Lb,i-1,a*(i-1));
    }

    s = output_p(Lb);
    return s;
}
