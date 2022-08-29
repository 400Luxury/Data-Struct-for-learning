#include "widget.h"
#include "ui_widget.h"
#include "myvec.h"
#include "mypolyn.h"
#include "myexpression.h"
#include "myfunction.h"
#include<bits/stdc++.h>
using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("计算器");
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_VectorButton_clicked()
{
    Myvec* form = new Myvec();
    form->show();
}

void Widget::on_PolynButton_clicked()
{
    Mypolyn* form = new Mypolyn();
    form->show();
}


void Widget::on_ExpreButton_clicked()
{
    Myexpression* form = new Myexpression();
    form->show();
}

void Widget::on_ExpreButton_2_clicked()
{
    Myfunction* form = new Myfunction();
    form->show();
}
