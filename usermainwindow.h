#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class userMainWindow;
}

class userMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit userMainWindow(QWidget *parent = nullptr);
    ~userMainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::userMainWindow *ui;
};

#endif // USERMAINWINDOW_H
