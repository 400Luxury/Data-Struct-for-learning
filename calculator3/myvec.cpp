#include "myvec.h"
#include "ui_myvec.h"
#include "sqlist.h"
#include<bits/stdc++.h>
using namespace std;

SqList a[LIST_INIT_NUM];
int cnt=0;
map<QString,int>mp;

Myvec::Myvec(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Myvec)
{
    ui->setupUi(this);
    setWindowTitle("向量计算");
}

Myvec::~Myvec()
{
    delete ui;
}

void Myvec::on_InitButton_clicked()
{
    QString name;
    name = ui->InitEdit1->text();
    if(!mp[name]) mp[name]=++cnt;
    InitList_Sq(a[mp[name]]);

    QString content;
    content = ui->InitEdit2->text();
    if(content[0]!='(' or content[content.size()-1]!=')')
    {
        ui->ResultEdit->setText("格式错误，请重新输入！");
        return;
    }
    if(content=="()")
    {
        ui->ResultEdit->setText("完成！");
        return;
    }

    content[content.size()-1]=',';
    QString tem=""; int nn=0;
    for (int i=1;i<content.size();i++) {
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
            float x=tem.toFloat();
            tem="";
            nn++;
            PutElem(a[mp[name]], nn, x);
        }
    }

    a[mp[name]].length=nn;
    ui->ResultEdit->setText("完成！");
    return;
}

void Myvec::on_LookButton_clicked()
{
    QString name;
    name=ui->LookEdit->text();
    if (!mp[name] || !a[mp[name]].elem)
    {
        ui->ResultEdit->setText("向量不存在！");
        return;
    }

    QString s = output_v(a[mp[name]]);
    ui->ResultEdit->setText(s);
    return;
}

void Myvec::on_AddButton_clicked()
{
    QString name1,name2,name3;
    name1 = ui->AddEdit1->text();
    name2 = ui->AddEdit2->text();
    name3 = ui->AddEdit3->text();
    if(!mp[name3]) mp[name3]=++cnt;
    InitList_Sq(a[mp[name3]]);

    if (!mp[name1] || !a[mp[name1]].elem || !mp[name2] || !a[mp[name2]].elem)
    {
        ui->ResultEdit->setText("向量不存在！");
        return;
    }

    QString s = Add_v(a[mp[name1]],a[mp[name2]],a[mp[name3]]);
    ui->ResultEdit->setText(s);
    return;
}


void Myvec::on_SubButton_clicked()
{
    QString name1,name2,name3;
    name1 = ui->SubEdit1->text();
    name2 = ui->SubEdit2->text();
    name3 = ui->SubEdit3->text();
    if(!mp[name3]) mp[name3]=++cnt;
    InitList_Sq(a[mp[name3]]);

    if (!mp[name1] || !a[mp[name1]].elem || !mp[name2] || !a[mp[name2]].elem)
    {
        ui->ResultEdit->setText("向量不存在！");
        return;
    }

    QString s = Substract_v(a[mp[name1]],a[mp[name2]],a[mp[name3]]);
    ui->ResultEdit->setText(s);
    return;
}


void Myvec::on_CosButton_clicked()
{
    QString name1,name2;
    name1 = ui->CosEdit1->text();
    name2 = ui->CosEdit2->text();

    if (!mp[name1] || !a[mp[name1]].elem || !mp[name2] || !a[mp[name2]].elem)
    {
        ui->ResultEdit->setText("向量不存在！");
        return;
    }

    if (a[mp[name1]].length != a[mp[name1]].length) {
        ui->ResultEdit->setText("维度不同，无法计算余弦值！");
    }
    else if (a[mp[name1]].length==1) {
        ui->ResultEdit->setText("一维向量之间无夹角！");
    }
    else {
        float cos = Cosine_Sq(a[mp[name1]],a[mp[name1]]);
        ui->ResultEdit->setText(QString("%1").arg(cos));
    }
    return;
}

void Myvec::on_ClearButton_clicked()
{
    QString name;
    name = ui->ClearEdit->text();
    if (!mp[name] || !a[mp[name]].elem)
    {
        ui->ResultEdit->setText("向量不存在！");
        return;
    }
    else {
        ClearList_Sq(a[mp[name]]);
        ui->ResultEdit->setText(name+"已清空！");
    }
}

void Myvec::on_DestroyButton_clicked()
{
    QString name;
    name = ui->DestroyEdit->text();
    if (!mp[name] || !a[mp[name]].elem)
    {
        ui->ResultEdit->setText("向量不存在！");
        return;
    }
    else {
        DestroyList_Sq(a[mp[name]]);
        mp.erase(name);
        ui->ResultEdit->setText(name+"已销毁！");
    }
}
