#ifndef MYFUNCTION_H
#define MYFUNCTION_H

#include <QDialog>

namespace Ui {
class Myfunction;
}

class Myfunction : public QDialog
{
    Q_OBJECT

public:
    explicit Myfunction(QWidget *parent = nullptr);
    ~Myfunction();

private slots:
    void on_DefButton_clicked();

    void on_RunButton_clicked();

    void on_ClearButton_clicked();

private:
    Ui::Myfunction *ui;
};

#endif // MYFUNCTION_H
