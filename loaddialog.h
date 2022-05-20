#ifndef LOADDIALOG_H
#define LOADDIALOG_H

#include <QDialog>

namespace Ui {
class LoadDialog;
}

class LoadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadDialog(QWidget *parent = nullptr);
    ~LoadDialog();

private slots:
    void on_pushButton_clicked();



private:
    Ui::LoadDialog *ui;
    void isSupreme(QString userName);//判断是否为supreme用户
};

#endif // LOADDIALOG_H
