#ifndef MYEXPRESSION_H
#define MYEXPRESSION_H

#include <QDialog>

namespace Ui {
class Myexpression;
}

class Myexpression : public QDialog
{
    Q_OBJECT

public:
    explicit Myexpression(QWidget *parent = nullptr);
    ~Myexpression();

private slots:
    void on_CalButton1_clicked();

    void on_CalButton2_clicked();

private:
    Ui::Myexpression *ui;
};

extern QString op;
extern int opRelation[6][7];

#endif // MYEXPRESSION_H
