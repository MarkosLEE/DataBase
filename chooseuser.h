#ifndef CHOOSEUSER_H
#define CHOOSEUSER_H

#include <QDialog>

namespace Ui {
class ChooseUser;
}

class ChooseUser : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseUser(QWidget *parent = nullptr);
    ~ChooseUser();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ChooseUser *ui;
};

#endif // CHOOSEUSER_H
