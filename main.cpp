#include "mainwindow.h"
#include"loaddialog.h"

#include <QApplication>
//关于这个extern变量的用法，即在最初的定义文件中，不需要extern声明，在使用处需要提前extern声明
//以及不能定义在头文件中！！！！因为这是在链接期起作用的，头文件是被包含（即粘贴复制一份），而不会被编译，
extern QSqlDatabase db;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainW;
    LoadDialog LoadD;
    if(LoadD.exec()==QDialog::Accepted){
        //这个地方需要一个判断账号是否已经注册、密码是否正确的函数

        db=QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");//主机名
        db.setDatabaseName("game");//数据库名
        db.setUserName("root");//管理员用户
        db.setPassword("");//此处填入对应的用户密码
        bool ok=db.open();
        if(ok)mainW.show();
        return a.exec();
    }
    else return 0;
}
