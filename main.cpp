#include "mainwindow.h"
#include"loaddialog.h"
#include"chooseuser.h"
#include <QApplication>
#include<QDebug>
//关于这个extern变量的用法，即在最初的定义文件中，不需要extern声明，在使用处需要提前extern声明
//以及不能定义在头文件中！！！！因为这是在链接期起作用的，头文件是被包含（即粘贴复制一份），而不会被编译，
extern QSqlDatabase db;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainW;
    LoadDialog LoadD;
    ChooseUser Choose;
    extern bool rootuser;
    Choose.exec();
    qDebug()<<rootuser<<endl;
    LoadD.exec();
    return a.exec();
}
