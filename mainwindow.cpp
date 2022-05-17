#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"insert.h"
#include<QTableView>
#include<QSqlQueryModel>
#include<QMessageBox>
#include<QSqlQuery>
#include<QDebug>
extern bool rootuser;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    QSqlQuery query;
    query.exec("show tables");
    while(query.next()){
        ui->comboBox->addItem(query.value(0).toString());
    }

}

//点击“显示”按钮的槽函数
void MainWindow::on_pushButton_3_clicked()
{
    model=new QSqlQueryModel(this);
    QString tablename=ui->comboBox->currentText();//当前选择的表名
    model->setQuery("select * from "+tablename);
    QSqlQuery query;//没有指定连接是因为整个程序只有一个连接，即db
    int i=0;
    query.exec("describe "+tablename);
    while (query.next()) {
        model->setHeaderData(i,Qt::Horizontal,query.value(0).toString());
        i++;
    }
    ui->tableView->setModel(model);
}

//点击“插入”按钮的槽函数
void MainWindow::on_pushButton_clicked()
{
    if(!rootuser)QMessageBox::warning(this,tr("错误"),tr("没有管理员权限，无法注册新用户！"));
    else{
        Insert* insertDi=new Insert(this);
        insertDi->exec();
    }

}

//点击“删除”按钮的槽函数
void MainWindow::on_pushButton_2_clicked()
{
    int i=ui->tableView->currentIndex().row();//获取当前选中的行号
    if(i<0){
        QMessageBox::warning(this,tr("错误"),tr("未选中要删除的数据行！"));
        return;
    }

    QSqlQuery query;
    QString cmd="delete from "+ui->comboBox->currentText()+" where ";
    for(int j=0; j<model->columnCount(); j++){
        auto ret=model->index(i,j);
        if(j==0)cmd=cmd+model->headerData(j,Qt::Horizontal,Qt::DisplayRole).toString()+"=\'"+model->data(ret).toString()+"\' ";
        else cmd=cmd+"and "+model->headerData(j,Qt::Horizontal,Qt::DisplayRole).toString()+"=\'"+model->data(ret).toString()+"\' ";
    }
    qDebug()<<cmd<<endl;
    query.exec(cmd);
}




