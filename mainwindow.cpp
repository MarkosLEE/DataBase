#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"insert.h"
#include<QTableView>
#include<QSqlQueryModel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
    QSqlQueryModel*model=new QSqlQueryModel(this);
    model->setQuery("select * from user");
    model->setHeaderData(0,Qt::Horizontal,"Uid");
    model->setHeaderData(1,Qt::Horizontal,"Uname");
    ui->tableView->setModel(model);
}


void MainWindow::on_pushButton_clicked()
{
    Insert* insertDi=new Insert(this);
    insertDi->exec();


}

