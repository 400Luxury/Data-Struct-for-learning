#include "myexpression.h"
#include "ui_myexpression.h"
#include "stack.h"
#include<bits/stdc++.h>
using namespace std;

Myexpression::Myexpression(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Myexpression)
{
    ui->setupUi(this);
    setWindowTitle("表达式求值");
}

Myexpression::~Myexpression()
{
    delete ui;
}

QString op = "+-*/^(#";
int opRelation[6][7]={ //top +  -  *  /  ^  (  #   //将进入
                            -1,-1,-1,-1,-1, 1, 1,  // +
                            -1,-1,-1,-1,-1, 1, 1,  // -
                             1, 1,-1,-1,-1, 1, 1,  // *
                             1, 1,-1,-1,-1, 1, 1,  // /
                             1, 1, 1, 1,-1, 1, 1,  // ^
                             1, 1, 1, 1, 1, 1, 1}; // (

bool check_op(QChar x) {
    //判断字符是否为运算符
    if(x=='+'||x=='-'||x=='*'||x=='/'||x=='('||x==')'||x=='^') return TRUE;
    return FALSE;
}

int check_float(QString s) {
    //判断字符串是否为合规的浮点数
    if(s=="") return -1;
    if (s[0]=='e' || s[s.length()-1]=='e') return 0;
    QString tem;
    for(int i=0; i<s.length(); i++) {
        if ( s[i].isDigit() || (s[i]=='e' && !tem.contains("e")) || (s[i]=='.' && !tem.contains(".")) || s[i]=='-') {
            tem += s[i];
        }
        else return 0;
    }
    return 1;
}

bool check_name(QString s) {
    //判断是否为合法的变量名
    if(s[0].isDigit()) return FALSE;
    for(int i=0; i<s.length(); i++) {
        if(s[i].isDigit() || (s[i]>='a'&&s[i]<='z') || (s[i]>='A'&&s[i]<='Z') || s[i]=='_') continue;
        else return FALSE;
    }
    return TRUE;
}

void Operate(QChar c, Stack_num &stk) {
    //从操作数中取两个操作数进行运算，并将计算结果压入操作数栈中
    float a,b,y;
    Pop_num(stk,b);
    Pop_num(stk,a);
    if(c=='+') y=a+b;
    if(c=='-') y=a-b;
    if(c=='*') y=a*b;
    if(c=='/') y=a/b;
    if(c=='^') y=pow(a,b);
    Push_num(stk,y);
    return;
}

void Myexpression::on_CalButton1_clicked()
{
    QString content = ui->ExpEdit1->text();
    if(!(content[0].isDigit()||content[0]=='.'||content[0]=='-'||content[0]=='(')) {
        ui->ResultEdit1->setText("格式错误，请重新输入！");
        return;
    }
    if(content[0]=='-') content.insert(0,QString("0"));

    Stack_op stk1;
    Stack_num stk2;
    InitStack_op(stk1);
    InitStack_num(stk2);
    Push_op(stk1,'#');

    QString elem = "";
    int i;
    for (i=0; i<content.length(); i++) {
        QChar tmp = content[i];
        if(!check_op(tmp) || (tmp=='-' && i>=2 && content[i-1]=='e' && content[i-2].isDigit()) ) elem.append(tmp);

        else {  //遇到运算符
            if(tmp=='(') {  //遇到左括号
                if(elem!="") {ui->ResultEdit1->setText("格式错误，请重新输入！"); return;}
                else if(i>0 && content[i-1]==')') {ui->ResultEdit1->setText("格式错误，请重新输入！"); return;}
                else Push_op(stk1,tmp);
            }  //左括号结束

            else if(tmp==')') {  //遇到右括号
                if(elem=="" && content[i-1]!=')') {ui->ResultEdit1->setText("格式错误，请重新输入！"); return;}
                else {
                    if(check_float(elem)==0) {ui->ResultEdit1->setText("格式错误，请重新输入！"); return;}
                    if(check_float(elem)==1) {Push_num(stk2,elem.toFloat()); elem="";}
                    while(!StackEmpty_op(stk1)) {
                        QChar c;
                        Pop_op(stk1,c);
                        if(c=='(') break;
                        Operate(c,stk2);
                    }
                }
            }  //右括号结束

            else{  //遇到+、-、*、/、^
                if(check_float(elem)==0) {ui->ResultEdit1->setText("格式错误，请重新输入！"); return;}
                if(check_float(elem)==-1) {
                    if(tmp=='-' && content[i-1]=='(') Push_num(stk2,0);  //'-'表负号时的特殊处理
                    else if(content[i-1]!=')') {ui->ResultEdit1->setText("格式错误，请重新输入！"); return;}
                }
                if(check_float(elem)==1) {
                    Push_num(stk2,elem.toFloat());
                    elem="";
                }
                while(!StackEmpty_op(stk1)){
                    QChar c;
                    GetTop_op(stk1,c);
                    int order = opRelation[op.indexOf(tmp)][op.indexOf(c)];
                    if(order==1) {
                        Push_op(stk1,tmp);
                        break;
                    }
                    else{
                        Pop_op(stk1,c);
                        Operate(c,stk2);
                    }
                }  //while
            }  //+、-、*、/、^结束
        }  //运算符结束
    }  //for，输入遍历完毕

    if(check_float(elem)==0 || (check_float(elem)==-1 && content[i-1]!=')') ) {ui->ResultEdit1->setText("格式错误，请重新输入！"); return;}
    if(check_float(elem)==1) Push_num(stk2,elem.toFloat());
    if(check_float(elem)==1 || content[i-1]==')') {
        while(!StackEmpty_op(stk1)){
            QChar c;
            Pop_op(stk1,c);
            if(c=='(') {ui->ResultEdit1->setText("格式错误，请重新输入！"); return;}  //存在未匹配的左括号
            if(c=='#') break;
            Operate(c,stk2);
        }
        if(stk2.top-stk2.base==1) {
            float ans;
            GetTop_num(stk2,ans);
            ui->ResultEdit1->setText(QString("%1").arg(ans));
            return;
        }
        else {ui->ResultEdit1->setText("格式错误，请重新输入！"); return;}
    }
}

void Myexpression::on_CalButton2_clicked()
{
    QString content = ui->ExpEdit2->text();
    QString Value = ui->ValueEdit->text();
    float value=0;
    QString name="";

    //检查输入合法性
    if(content==""||Value=="") {ui->ResultEdit2->setText("请输入表达式和变量值！"); return;}

    if(check_float(Value)==1) value = Value.toFloat();
    else{ui->ResultEdit2->setText("变量值不合法！"); return;}

    if(content[0]=='+'||content[0]=='*'||content[0]=='/'||content[0]=='^'||content[0]==')') {
        ui->ResultEdit2->setText("格式错误，请重新输入！");
        return;
    }
    if(content[0]=='-') content.insert(0,QString("0"));

    Stack_op stk1;
    Stack_num stk2;
    InitStack_op(stk1);
    InitStack_num(stk2);
    Push_op(stk1,'#');

    QString elem = "";
    int i;
    for (i=0; i<content.length(); i++) {
        QChar tmp = content[i];
        if(!check_op(tmp) || (tmp=='-' && i>=2 && content[i-1]=='e' && content[i-2].isDigit()) ) elem.append(tmp);

        else {  //遇到运算符
            if(tmp=='(') {  //遇到左括号
                if(elem!="") {ui->ResultEdit2->setText("格式错误，请重新输入！"); return;}
                else if(i>0 && content[i-1]==')') {ui->ResultEdit2->setText("格式错误，请重新输入！"); return;}
                else Push_op(stk1,tmp);
            }  //左括号结束

            else if(tmp==')') {  //遇到右括号
                if(elem=="" && content[i-1]!=')') {ui->ResultEdit2->setText("格式错误，请重新输入！"); return;}
                else {
                    if(check_float(elem)==0) {
                        if(check_name(elem)) {
                            if(name=="") name=elem;
                            else if(elem!=name) {ui->ResultEdit2->setText("格式错误，请重新输入！"); return;}
                            Push_num(stk2,value);
                        }
                        else {ui->ResultEdit2->setText("格式错误，请重新输入！"); return;}
                    }
                    if(check_float(elem)==1) Push_num(stk2,elem.toFloat());
                    elem="";
                    while(!StackEmpty_op(stk1)) {
                        QChar c;
                        Pop_op(stk1,c);
                        if(c=='(') break;
                        Operate(c,stk2);
                    }
                }
            }  //右括号结束

            else{  //遇到+、-、*、/、^
                if(check_float(elem)==0) {
                    if(check_name(elem)) {
                        if(name=="") name=elem;
                        else if(elem!=name) {ui->ResultEdit2->setText("格式错误，请重新输入！"); return;}
                        Push_num(stk2,value);
                    }
                    else {ui->ResultEdit2->setText("格式错误，请重新输入！"); return;}
                }
                if(check_float(elem)==-1) {
                    if(tmp=='-' && content[i-1]=='(') Push_num(stk2,0);  //'-'表负号时的特殊处理
                    else if(content[i-1]!=')') {ui->ResultEdit2->setText("格式错误，请重新输入！"); return;}
                }
                if(check_float(elem)==1)  Push_num(stk2,elem.toFloat());
                elem="";
                while(!StackEmpty_op(stk1)){
                    QChar c;
                    GetTop_op(stk1,c);
                    int order = opRelation[op.indexOf(tmp)][op.indexOf(c)];
                    if(order==1) {
                        Push_op(stk1,tmp);
                        break;
                    }
                    else{
                        Pop_op(stk1,c);
                        Operate(c,stk2);
                    }
                }  //while
            }  //+、-、*、/、^结束
        }  //运算符结束
    }  //for，输入遍历完毕

    if(check_float(elem)==0) {
        if(check_name(elem)) {
            if(name=="") name=elem;
            else if(elem!=name) {ui->ResultEdit2->setText("格式错误，请重新输入！"); return;}
            Push_num(stk2,value);
        }
        else {ui->ResultEdit2->setText("格式错误，请重新输入！"); return;}
    }
    if(check_float(elem)==-1 && content[i-1]!=')') {ui->ResultEdit2->setText("格式错误，请重新输入！"); return;}
    if(check_float(elem)==1) Push_num(stk2,elem.toFloat());
    if(check_float(elem)==1 || content[i-1]==')' || elem==name) {
        while(!StackEmpty_op(stk1)){
            QChar c;
            Pop_op(stk1,c);
            if(c=='(') {ui->ResultEdit2->setText("格式错误，请重新输入！"); return;}  //存在未匹配的左括号
            if(c=='#') break;
            Operate(c,stk2);
        }
        if(stk2.top-stk2.base==1) {
            float ans;
            GetTop_num(stk2,ans);
            ui->ResultEdit2->setText(QString("%1").arg(ans));
            return;
        }
        else {ui->ResultEdit2->setText("格式错误，请重新输入！"); return;}
    }
}
