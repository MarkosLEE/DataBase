#include"global.h"


update::update(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::update)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("修改"));
}

update::~update()
{
    delete ui;
    delete [] input;
}

void update::init(QString name,QSqlQueryModel*model,int row)
{
    this->row=row;
    this->tablename=name;
    this->model=model;
    input=new QLineEdit[1];
    if(name=="team_has_player")ui->formLayout->addRow("isLeader",input);
    else ui->formLayout->addRow("isBanned",input);
}

void update::init(QSqlQuery query, QString tablename,QSqlQueryModel*model,int row)
{
    this->row=row;
    this->model=model;
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
//点击取消按钮
void update::on_pushButton_clicked()
{
    this->close();
}

//点击确认按钮
void update::on_pushButton_2_clicked()
{
    QSqlQuery update;
    QString cmd="update "+this->tablename+" set ";
    //此时为修改true,false
    if(ui->formLayout->rowCount()==1){
        QString content=this->input[0].text();
        if(content!="true"&&content!="false"){
            QMessageBox::warning(this,tr("错误"),"内容错误，请重新输入修改后的内容！");
        }
        if(this->tablename=="team_has_player"){
            cmd=cmd+"isLeader='"+content+"'";
        }
        else cmd=cmd+"isBanned='"+content+"'";
    }
    else{
        query.first();
        int i=0;
        cmd=cmd+query.value(0).toString()+"='"+this->input[i].text()+"',";
        while (query.next()) {
           i++;
           cmd=cmd+query.value(0).toString()+"='"+this->input[i].text()+"',";
        }
        cmd.remove(cmd.size()-1,1);//去除最后多余的逗号
    }
    cmd=cmd+" where ";
    for(int j=0; j<model->columnCount(); j++){
        auto ret=model->index(this->row,j);
        if(j==0)cmd=cmd+model->headerData(j,Qt::Horizontal,Qt::DisplayRole).toString()+"=\'"+model->data(ret).toString()+"\' ";
        else cmd=cmd+"and "+model->headerData(j,Qt::Horizontal,Qt::DisplayRole).toString()+"=\'"+model->data(ret).toString()+"\' ";
    }
    qDebug()<<cmd<<endl;
    bool res=update.exec(cmd);
    if(!res){
        QMessageBox::warning(this,tr("错误"),update.lastError().text());
    }
    this->close();
}

