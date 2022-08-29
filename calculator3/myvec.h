#ifndef MYVEC_H
#define MYVEC_H

#include <QDialog>

namespace Ui {
class Myvec;
}

class Myvec : public QDialog
{
    Q_OBJECT

public:
    explicit Myvec(QWidget *parent = nullptr);
    ~Myvec();

private slots:
    void on_InitButton_clicked();

    void on_LookButton_clicked();

    void on_AddButton_clicked();

    void on_SubButton_clicked();

    void on_CosButton_clicked();

    void on_ClearButton_clicked();

    void on_DestroyButton_clicked();

private:
    Ui::Myvec *ui;
};

#endif // MYVEC_H
