#include "loaddialog.h"
#include "ui_loaddialog.h"
#include "register.h"
#include "global.h"
#include "mainwindow.h"
#include "usermainwindow.h"
#include<QMessageBox>
extern QSqlDatabase db;
extern bool rootuser;
LoadDialog::LoadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("登录");
}

LoadDialog::~LoadDialog()
{
    delete ui;
}

void LoadDialog::on_pushButton_clicked()
{
    QString username=ui->LineEdit->text();
    QString hostname=ui->LineEdit_2->text();
    QString password=ui->LineEdit_3->text();
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(hostname);//主机名
    db.setDatabaseName("game");//数据库名
    db.setUserName(username);//管理员用户
    db.setPassword(password);//此处填入对应的用户密码
    bool ok=db.open();
    if(ok){
        this->close();
            MainWindow *rootMainWindow=new MainWindow(this);

            rootMainWindow->show();
    }
    else{
        QMessageBox::warning(this,tr("错误"),tr("连接数据库失败，请检查用户名、主机名以及密码是否正确"));
    }
}


void LoadDialog::on_pushButton_2_clicked()
{
    //如果是管理员用户登录，则允许注册新用户
    if(rootuser){
        Register* r=new Register;
        r->setWindowTitle("注册");
        r->exec();
    }
    //不是则弹窗报错
    else{
        QMessageBox::warning(this,tr("错误"),tr("没有管理员权限，无法注册新用户！"));
    }
}

