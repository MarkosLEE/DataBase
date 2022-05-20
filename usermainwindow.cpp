#include "usermainwindow.h"
#include "ui_usermainwindow.h"
#include<QTableView>
#include<QSqlQueryModel>
userMainWindow::userMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::userMainWindow)
{
    ui->setupUi(this);
}

userMainWindow::~userMainWindow()
{
    delete ui;
}

void userMainWindow::on_pushButton_clicked()
{
    QSqlQueryModel*model=new QSqlQueryModel(this);
    model->setQuery("select * from user");
    model->setHeaderData(0,Qt::Horizontal,"Uid");
    model->setHeaderData(1,Qt::Horizontal,"Uname");
    ui->tableView->setModel(model);
}

