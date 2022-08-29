#ifndef MYPOLYN_H
#define MYPOLYN_H

#include <QDialog>

namespace Ui {
class Mypolyn;
}

class Mypolyn : public QDialog
{
    Q_OBJECT

public:
    explicit Mypolyn(QWidget *parent = nullptr);
    ~Mypolyn();

private slots:
    void on_InitButton_clicked();

    void on_LookButton_clicked();

    void on_AddButton_clicked();

    void on_SubButton_clicked();

    void on_MultiButton_clicked();

    void on_DeriButton_clicked();

    void on_ClearButton_clicked();

    void on_DestroyButton_clicked();

private:
    Ui::Mypolyn *ui;
};

#endif // MYPOLYN_H
