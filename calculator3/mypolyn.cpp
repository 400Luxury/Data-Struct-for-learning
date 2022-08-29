#include "mypolyn.h"
#include "ui_mypolyn.h"
#include "sqlist.h"
#include "linklist.h"

// 处理交互文本输入1
SqList a1[LIST_INIT_NUM];
int cnt1=0;
map<QString,int>mp1;

//处理交互文本输入2
LinkList a2[LIST_INIT_NUM];
int cnt2=0;
map<QString,int>mp2;

Mypolyn::Mypolyn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mypolyn)
{
    ui->setupUi(this);
    setWindowTitle("一元多项式计算");
}

Mypolyn::~Mypolyn()
{
    delete ui;
}

void Mypolyn::on_InitButton_clicked()
{
    int mode = ui->comboBox->currentIndex();
    QString name = ui->InitEdit1->text();
    QString content = ui->InitEdit2->text();
    content.append(" ");
    QString tem = "";
    int flag = 0;

    if (mode==0) {      //顺序表模式
        if(!mp1[name]) mp1[name]=++cnt1;
        InitList_Sq(a1[mp1[name]]);
        SqList* L1 = &a1[mp1[name]];
        float coef = 0.;
        int expn = 0, max_expn = 0;
        for (int t=1; t<=LIST_INIT_SIZE; t++) {
            PutElem(*L1, t, 0);
        }

        for (int i=0; i<content.length(); i++) {
            if (content[i]!=" ") {
                if (content[i]!=',') {
                    if ((content[i]>='0' && content[i]<='9') || (content[i]=='-' && tem=="") || (content[i]=='.' && !tem.contains(".")))
                        tem+=content[i];
                    else {
                        ui->ResultEdit->setText("格式错误，请重新输入！");
                        return;
                    }
                }
                else {
                    if (content[i-1]=='-') {
                        ui->ResultEdit->setText("格式错误，请重新输入！");
                        return;
                    }
                    flag++;
                    coef = tem.toFloat();
                    tem="";
                }
            }
            else {      //content[i]==" "
                if (flag != 1) {
                    ui->ResultEdit->setText("格式错误，请重新输入！");
                    return;
                }
                if (content[i-1]=='-') {
                    ui->ResultEdit->setText("格式错误，请重新输入！");
                    return;
                }
                if (content[i-1]>='0' && content[i]<='9') {
                    if (tem.contains("-") || tem.contains("."))
                    {
                        ui->ResultEdit->setText("格式错误，请重新输入！");
                        return;
                    }
                    expn = tem.toInt();
                    if (expn>max_expn) max_expn = expn;
                    tem=""; flag = 0;
                    float e = 0;
                    if (GetElem(*L1, expn+1, e)){
                        if (fabs(e)<=1e-6) PutElem(*L1, expn+1, coef);
                        else PutElem(*L1, expn+1, e+coef);
                    }
                    else PutElem(*L1, expn+1, coef);
                }
                else {
                    ui->ResultEdit->setText("格式错误，请重新输入！");
                    return;
                }
            }
        } //for

        a1[mp1[name]].length = max_expn+1;
        ui->ResultEdit->setText("完成！");
        return;
    }

    //链表模式
    if(!mp2[name]) mp2[name]=++cnt2;
    InitList(a2[mp2[name]]);
    LinkList* L2 = &a2[mp2[name]];
    ElemType_p e;

    for (int i=0; i<content.length(); i++) {
        if (content[i]!=" ") {
            if (content[i]!=',') {
                if ((content[i]>='0' && content[i]<='9') || (content[i]=='-' && tem=="") || (content[i]=='.' && !tem.contains(".")))
                    tem+=content[i];
                else {
                    ui->ResultEdit->setText("格式错误，请重新输入！");
                    return;
                }
            }
            else {
                if (content[i-1]=='-') {
                    ui->ResultEdit->setText("格式错误，请重新输入！");
                    return;
                }
                flag++;
                e.coef = tem.toFloat();
                tem = "";
            }
        }
        else {      //content[i]==" "
            if (flag != 1) {
                ui->ResultEdit->setText("格式错误，请重新输入！");
                return;
            }
            if (content[i-1]=='-') {
                ui->ResultEdit->setText("格式错误，请重新输入！");
                return;
            }
            if (content[i-1]>='0' && content[i]<='9') {
                if (tem.contains("-") || tem.contains("."))
                {
                    ui->ResultEdit->setText("格式错误，请重新输入！");
                    return;
                }
                e.expn = tem.toInt();
                tem=""; flag = 0;
                if (e.coef == 0) continue;
                PutList(*L2, e);
            }
            else {
                ui->ResultEdit->setText("格式错误，请重新输入！");
                return;
            }
        }
    } //for

    ui->ResultEdit->setText("完成！");
    return;
}

void Mypolyn::on_LookButton_clicked()
{
    int mode = ui->comboBox->currentIndex();
    QString name= ui->LookEdit->text();
    QString s;
    if (mode==0) {
        if (!mp1[name])
        {
            ui->ResultEdit->setText("多项式不存在！");
            return;
        }

        s = output_p(a1[mp1[name]]);
        ui->ResultEdit->setText(s);
        return;
    }

    if (!mp2[name])
    {
        ui->ResultEdit->setText("多项式不存在！");
        return;
    }

    s = output_pl(a2[mp2[name]]);
    ui->ResultEdit->setText(s);
    return;
}

void Mypolyn::on_AddButton_clicked()
{
    int mode = ui->comboBox->currentIndex();
    QString name1, name2, name3;
    name1 = ui->AddEdit1->text();
    name2 = ui->AddEdit2->text();
    name3 = ui->AddEdit3->text();

    if (mode==0) {
        if(!mp1[name3]) mp1[name3]=++cnt1;
        InitList_Sq(a1[mp1[name3]]);

        if (!mp1[name1] || !mp1[name2])
        {
            ui->ResultEdit->setText("多项式不存在！");
            return;
        }

        QString s = Add_p(a1[mp1[name1]],a1[mp1[name2]],a1[mp1[name3]]);
        ui->ResultEdit->setText(s);
        return;
    }

    if(!mp2[name3]) mp2[name3]=++cnt2;
    InitList(a2[mp2[name3]]);

    if (!mp2[name1] || !mp2[name2])
    {
        ui->ResultEdit->setText("多项式不存在！");
        return;
    }

    QString s = Add_pl(a2[mp2[name1]],a2[mp2[name2]],a2[mp2[name3]]);
    ui->ResultEdit->setText(s);
    return;
}

void Mypolyn::on_SubButton_clicked()
{
    int mode = ui->comboBox->currentIndex();
    QString name1, name2, name3;
    name1 = ui->SubEdit1->text();
    name2 = ui->SubEdit2->text();
    name3 = ui->SubEdit3->text();

    if (mode==0) {
        if(!mp1[name3]) mp1[name3]=++cnt1;
        InitList_Sq(a1[mp1[name3]]);

        if (!mp1[name1] || !mp1[name2])
        {
            ui->ResultEdit->setText("多项式不存在！");
            return;
        }

        QString s = Substract_p(a1[mp1[name1]],a1[mp1[name2]],a1[mp1[name3]]);
        ui->ResultEdit->setText(s);
        return;
    }

    if(!mp2[name3]) mp2[name3]=++cnt2;
    InitList(a2[mp2[name3]]);

    if (!mp2[name1] || !mp2[name2])
    {
        ui->ResultEdit->setText("多项式不存在！");
        return;
    }

    QString s = Substract_pl(a2[mp2[name1]],a2[mp2[name2]],a2[mp2[name3]]);
    ui->ResultEdit->setText(s);
    return;
}



void Mypolyn::on_MultiButton_clicked()
{
    int mode = ui->comboBox->currentIndex();
    QString name1, name2, name3;
    name1 = ui->MultiEdit1->text();
    name2 = ui->MultiEdit2->text();
    name3 = ui->MultiEdit3->text();

    if (mode==0) {
        if(!mp1[name3]) mp1[name3]=++cnt1;
        InitList_Sq(a1[mp1[name3]]);
        for (int t=1; t<=LIST_INIT_SIZE; t++) {
            PutElem(a1[mp1[name3]], t, 0);
        }

        if (!mp1[name1] || !mp1[name2])
        {
            ui->ResultEdit->setText("多项式不存在！");
            return;
        }

        QString s = Multiply_p(a1[mp1[name1]],a1[mp1[name2]],a1[mp1[name3]]);
        ui->ResultEdit->setText(s);
        return;
    }

    if(!mp2[name3]) mp2[name3]=++cnt2;
    InitList(a2[mp2[name3]]);

    if (!mp2[name1] || !mp2[name2])
    {
        ui->ResultEdit->setText("多项式不存在！");
        return;
    }

    QString s = Multiply_pl(a2[mp2[name1]],a2[mp2[name2]],a2[mp2[name3]]);
    ui->ResultEdit->setText(s);
    return;
}


void Mypolyn::on_DeriButton_clicked()
{
    int mode = ui->comboBox->currentIndex();
    QString name1, name2;
    name1 = ui->DeriEdit1->text();
    name2 = ui->DeriEdit2->text();
    if (mode==0) {
        if(!mp1[name2]) mp1[name2]=++cnt1;
        InitList_Sq(a1[cnt1]);
        for (int t=1; t<=LIST_INIT_SIZE; t++) {
            PutElem(a1[cnt1], t, 0);
        }

        if (!mp1[name1])
        {
            ui->ResultEdit->setText("多项式不存在！");
            return;
        }

        QString s = Deri_p(a1[mp1[name1]],a1[mp1[name2]]);
        ui->ResultEdit->setText(s);
        return;
    }

    if(!mp2[name2]) mp2[name2]=++cnt2;
    InitList(a2[mp2[name2]]);

    if (!mp2[name1])
    {
        ui->ResultEdit->setText("多项式不存在！");
        return;
    }

    QString s = Deri_pl(a2[mp2[name1]],a2[mp2[name2]]);
    ui->ResultEdit->setText(s);
    return;
}

void Mypolyn::on_ClearButton_clicked()
{
    int mode = ui->comboBox->currentIndex();
    QString name;
    name = ui->ClearEdit->text();
    if (mode == 0) {
        if (!mp1[name])
        {
            ui->ResultEdit->setText("向量不存在！");
            return;
        }
        else {
            ClearList_Sq(a1[mp1[name]]);
            ui->ResultEdit->setText(name+"已清空！");
        }
        return;
    }

    if (!mp2[name])
    {
        ui->ResultEdit->setText("向量不存在！");
        return;
    }
    else {
        ClearList(a2[mp2[name]]);
        ui->ResultEdit->setText(name+"已清空！");
    }
    return;
}

void Mypolyn::on_DestroyButton_clicked()
{
    int mode = ui->comboBox->currentIndex();
    QString name;
    name = ui->DestroyEdit->text();
    if (mode == 0) {
        if (!mp1[name])
        {
            ui->ResultEdit->setText("向量不存在！");
            return;
        }
        else {
            DestroyList_Sq(a1[mp1[name]]);
            mp1.erase(name);
            ui->ResultEdit->setText(name+"已销毁！");
        }
        return;
    }

    if (!mp2[name])
    {
        ui->ResultEdit->setText("向量不存在！");
        return;
    }
    else {
        DestroyList(a2[mp2[name]]);
        mp2.erase(name);
        ui->ResultEdit->setText(name+"已销毁！");
    }
    return;
}
