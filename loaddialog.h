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

    void on_pushButton_2_clicked();

private:
    Ui::LoadDialog *ui;
};

#endif // LOADDIALOG_H
