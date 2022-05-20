#include"global.h"
Insert::Insert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Insert)
{
    ui->setupUi(this);
}

Insert::~Insert()
{
    delete ui;
    if(this->input!=nullptr)delete [] input;
}

void Insert::on_pushButton_2_clicked()
{
    QSqlQuery insert;
    //这里遇到了一个大坑，即string的加法操作符两边不能同时是右值
    //QString cmd="insert into user(Uid,Uname) values(\'"+ui->uidLineEdit->text()+"\',\'"+ui->unameLineEdit->text()+"\')";
    //qDebug()<<cmd;
    //insert.exec(cmd);
    QString cmd="insert into "+this->tablename+"(";
    int num=query.size();//属性的个数
    query.first();
    cmd=cmd+query.value(0).toString()+",";
    while (query.next()) {
       cmd=cmd+query.value(0).toString()+",";
    }
    cmd.remove(cmd.size()-1,1);//去除最后多余的逗号
    cmd=cmd+") values(";
    for(int i=0; i<num; i++){
        if(i!=num-1)cmd=cmd+"\'"+this->input[i].text()+"\',";
        else cmd=cmd+"\'"+this->input[i].text()+"\')";
    }
    qDebug()<<cmd;
    bool res=insert.exec(cmd);
    if(!res){
        QMessageBox::warning(this,tr("错误"),insert.lastError().text());
    }
    this->close();
}


void Insert::on_pushButton_clicked()
{
    this->close();
}
void Insert::init(QSqlQuery query,QString tablename)
{
    this->setWindowTitle(tr("插入"));
    this->query=query;
    this->tablename=tablename;
    this->input=new QLineEdit[query.size()];
    int num=0;//属性的个数
    while(query.next()){
        ui->formLayout->addRow(query.value(0).toString(),&input[num]);
        num++;
    }
}
