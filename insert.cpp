#include "insert.h"
#include "ui_insert.h"

#include<QSqlQuery>
#include<QDebug>
Insert::Insert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Insert)
{
    ui->setupUi(this);
}

Insert::~Insert()
{
    delete ui;
}

void Insert::on_pushButton_2_clicked()
{
    QSqlQuery insert;
    //这里遇到了一个大坑，即string的加法操作符两边不能同时是右值
    QString cmd="insert into user(Uid,Uname) values(\'"+ui->uidLineEdit->text()+"\',\'"+ui->unameLineEdit->text()+"\')";
    qDebug()<<cmd;
    insert.exec(cmd);
    this->close();
}


void Insert::on_pushButton_clicked()
{
    this->close();
}

