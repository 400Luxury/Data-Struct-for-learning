#include "expression.h"
#include "ui_expression.h"

Expression::Expression(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Expression)
{
    ui->setupUi(this);
}

Expression::~Expression()
{
    delete ui;
}
