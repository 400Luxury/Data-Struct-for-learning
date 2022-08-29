#include "myfunction.h"
#include "myexpression.h"
#include "ui_myfunction.h"
#include "stack.h"
#include "QDebug"
#include<bits/stdc++.h>
using namespace std;

Myfunction::Myfunction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Myfunction)
{
    ui->setupUi(this);
    setWindowTitle("定义函数求值");
}

Myfunction::~Myfunction()
{
    delete ui;
}

map<QString, QString> mpf;

bool check_op(QChar x);  //判断字符是否为运算符
int check_float(QString s);  //判断字符串是否为合规的浮点数(1:是，0:否，-1:空）
bool check_name(QString s);  //判断是否为合法的变量名
void Operate(QChar c, Stack_num &stk);  //从操作数中取两个操作数进行运算，并将计算结果压入操作数栈中

bool calculate(QString content, float &result)
{
    if(content[0]=='+'||content[0]=='*'||content[0]=='/'||content[0]=='^'||content[0]==')') return FALSE;
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
                if(elem!="") return FALSE;
                else if(i>0 && content[i-1]==')') return FALSE;
                else Push_op(stk1,tmp);
            }  //左括号结束

            else if(tmp==')') {  //遇到右括号
                if(elem=="" && content[i-1]!=')') return FALSE;
                else {
                    if(check_float(elem)==0) return FALSE;
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
                if(check_float(elem)==0) return FALSE;
                if(check_float(elem)==-1) {
                    if(tmp=='-' && content[i-1]=='(') Push_num(stk2,0);  //'-'表负号时的特殊处理
                    else if(content[i-1]!=')') return FALSE;
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

    if(check_float(elem)==0 || (check_float(elem)==-1 && content[i-1]!=')') ) return FALSE;
    if(check_float(elem)==1) Push_num(stk2,elem.toFloat());
    if(check_float(elem)==1 || content[i-1]==')') {
        while(!StackEmpty_op(stk1)){
            QChar c;
            Pop_op(stk1,c);
            if(c=='(') return FALSE;  //存在未匹配的左括号
            if(c=='#') break;
            Operate(c,stk2);
        }
        if(stk2.top-stk2.base==1) {
            GetTop_num(stk2,result);
            return TRUE;
        }
        else return FALSE;
    }
}

bool calculate(QString content, QString name, float value, float &result)
{
    if(content[0]=='+'||content[0]=='*'||content[0]=='/'||content[0]=='^'||content[0]==')') return FALSE;
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
                if(elem!="") return FALSE;
                else if(i>0 && content[i-1]==')') return FALSE;
                else Push_op(stk1,tmp);
            }  //左括号结束

            else if(tmp==')') {  //遇到右括号
                if(elem=="" && content[i-1]!=')') return FALSE;
                else {
                    if(check_float(elem)==0) {
                        if(elem == name) Push_num(stk2,value);
                        else return FALSE;
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
                    if(elem == name) Push_num(stk2,value);
                    else return FALSE;
                }
                if(check_float(elem)==-1) {
                    if(tmp=='-' && content[i-1]=='(') Push_num(stk2,0);  //'-'表负号时的特殊处理
                    else if(content[i-1]!=')') return FALSE;
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
        if(elem == name) Push_num(stk2,value);
        else return FALSE;
    }
    if(check_float(elem)==-1 && content[i-1]!=')') return FALSE;
    if(check_float(elem)==1) Push_num(stk2,elem.toFloat());
    if(check_float(elem)==1 || content[i-1]==')' || elem==name) {
        while(!StackEmpty_op(stk1)){
            QChar c;
            Pop_op(stk1,c);
            if(c=='(') return FALSE;  //存在未匹配的左括号
            if(c=='#') break;
            Operate(c,stk2);
        }
        if(stk2.top-stk2.base==1) {
            GetTop_num(stk2,result);
            return TRUE;
        }
        else return FALSE;
    }
}

void vari_replace(QString &content, QString s)
{
    // 解析已定义函数表达式content中的变量名并用s替换
    QString elem = "", x = "";

    for (int i=0; i<content.length(); i++) {
        QChar tmp = content[i];
        if(!check_op(tmp)) elem.append(tmp);

        else {  //遇到运算符
           if(check_float(elem)==0 && check_name(elem)==1) {
               x = elem;
               break;
           }
           else elem = "";
        }
    }

    if(elem!="" && check_name(elem)) x = elem;
    if(x!="") content.replace(x,s);
    return;
}

bool func_replace(QString &content)
{
    QString elem = "";

    for(int i=0; i<content.length(); i++) {
        QChar tmp = content[i];
        if(!check_op(tmp)) elem.append(tmp);
        else {  //遇到运算符
            if(tmp=='(' && elem!="") {  //遇到左括号
                if(mpf.count(elem)==0) return FALSE;
                else {
                    QString exp = mpf[elem];
                    int start = i-elem.length();
                    QString s="(";
                    for(int j=i+1; j<content.length(); j++) {
                        int tmpcnt = 0;
                        s.append(content[j]);
                        if(content[j]=='(') tmpcnt++;
                        else if(content[j]==')' && tmpcnt!=0) tmpcnt--;
                        else if(content[j]==')' && tmpcnt==0) {
                            //替换回溯
                            content.remove(start, j-start+1);
                            vari_replace(exp,s);
                            exp.insert(0,'(');
                            exp.append(')');
                            content.insert(start,exp);
                            i = start-1;
                            break;
                        }
                        if(j==content.length()-1) return FALSE;
                    }
                }
            }
            elem="";
        }
    }  //for

    return TRUE;
}

void del_func_text(QString &text, QString name)
{
    QStringList Lines = text.split('\n');
    for (int i=0; i<Lines.size(); i++) {
        if(Lines[i].indexOf(name)==0) {
            Lines[i] = "";
            break;
        }
    }
    text="";
    for (int i=0; i<Lines.size(); i++) {
        if(Lines[i]!=""){
            text.append(Lines[i]+'\n');
        }
    }
}

void Myfunction::on_DefButton_clicked()
{
    QString func_name = "", variable = "";
    QString func_exp = "";
    QString input = ui->DefEdit->text();
    float ans;
    if(input=="") {ui->ResultEdit->setText("请输入内容！"); return;}
    if(input[0].isDigit() || input[0]=='(') {ui->ResultEdit->setText("格式错误，请重新输入！"); return;}
    int i=0;
    while(input[i] != '(' && i<input.length()) {
        if(input[i].isDigit() || (input[i]>='a'&&input[i]<='z') || (input[i]>='A'&&input[i]<='Z') || input[i]=='_') {
            func_name.append(input[i]);
            i++;
        }
        else {ui->ResultEdit->setText("格式错误，请重新输入！"); return;}
    }

    if(i==input.length()) {ui->ResultEdit->setText("格式错误，请重新输入！"); return;}
    i++;
    while(input[i] != ')' && i<input.length()) {
        if(input[i].isDigit() || (input[i]>='a'&&input[i]<='z') || (input[i]>='A'&&input[i]<='Z') || input[i]=='_') {
            variable.append(input[i]);
            i++;
        }
        else {ui->ResultEdit->setText("格式错误，请重新输入！"); return;}
    }
    if(variable=="" || i>=input.length()-1) {ui->ResultEdit->setText("格式错误，请重新输入！"); return;}

    i++;
    if(input[i]!='=') {ui->ResultEdit->setText("格式错误，请重新输入！"); return;}

    i++;
    while(i<input.length()) {
        func_exp.append(input[i]);
        i++;
    }

    if(func_replace(func_exp) && calculate(func_exp,variable,1,ans)) {
        if(mpf.count(func_name)) {
            QString text = ui->textBrowser->toPlainText();
            del_func_text(text,func_name);
            ui->textBrowser->setText(text);
        }
        mpf[func_name]=func_exp;
        ui->ResultEdit->setText("完成！");
        ui->textBrowser->insertPlainText(input+"\n");
        ui->textBrowser->moveCursor(QTextCursor::Start);
        return;
    }
    else {ui->ResultEdit->setText("格式错误，请重新输入！"); return;}
}

void Myfunction::on_RunButton_clicked()
{
    QString input = ui->RunEdit->text();
    float ans;
    if(func_replace(input) && calculate(input,ans)) {
        ui->ResultEdit->setText(QString("%1").arg(ans));
        return;
    }
    else {ui->ResultEdit->setText("格式错误，请重新输入！"); return;}
}

void Myfunction::on_ClearButton_clicked()
{
    QString func_name = ui->ClearEdit->text();
    if(mpf.count(func_name)) {
        mpf.erase(func_name);
        ui->ResultEdit->setText("完成！");
        QString text = ui->textBrowser->toPlainText();
        del_func_text(text,func_name);
        ui->textBrowser->setText(text);
    }
    else ui->ResultEdit->setText("该函数不存在！");
    return;
}
