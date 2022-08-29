#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <QDialog>

namespace Ui {
class Expression;
}

class Expression : public QDialog
{
    Q_OBJECT

public:
    explicit Expression(QWidget *parent = nullptr);
    ~Expression();

private:
    Ui::Expression *ui;
};

#endif // EXPRESSION_H
