#include "mainwindow.h"
#include"loaddialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainW;
    LoadDialog LoadD;
    if(LoadD.exec()==QDialog::Accepted){
        //这个地方需要一个判断账号是否已经注册、密码是否正确的函数
        mainW.show();
        return a.exec();
    }
    else return 0;
}
