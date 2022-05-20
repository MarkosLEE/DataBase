#include"global.h"
extern bool supremeUser;
extern bool supremeUserRegister;
extern QSqlDatabase db;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_4->adjustSize();
    ui->pushButton_5->adjustSize();

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
    if(this->userName=="root")ui->label_2->setText(tr("当前用户为：Root User"));
    else if(supremeUser)ui->label_2->setText(tr("当前用户为：Supreme User"));
    else ui->label_2->setText(tr("当前用户为：Lower User"));
    ui->label_2->adjustSize();
    ui->label->adjustSize();
    this->showData();
}

//点击“修改”按钮的槽函数
void MainWindow::on_pushButton_3_clicked()
{
    int i=ui->tableView->currentIndex().row();//获取当前选中的行号

    if(i<0){
        QMessageBox::warning(this,tr("错误"),tr("未选中要修改的数据行！"));
        return;
    }

    QString tablename=ui->comboBox->currentText();//当前表名
    class update*updateDi=new class update(this);//这里犯了一个错，update这个类名与QWidget类的静态成员变量重名了
    if(tablename=="server_has_player"||tablename=="team_has_player"){
        updateDi->init(tablename,this->model,i);
        updateDi->exec();
    }
    else if(tablename=="player"||tablename=="server"||tablename=="domainname"){
        QSqlQuery query;
        query.exec("describe "+tablename);
        updateDi->init(query,tablename,this->model,i);
        updateDi->exec();
    }
    else {
        QMessageBox::warning(this,tr("错误"),tr("没有操作这些表的权限！"));
    }
    this->showData();
}

//点击“插入”按钮的槽函数
void MainWindow::on_pushButton_clicked()
{
    if(!supremeUser)QMessageBox::warning(this,tr("错误"),tr("没有管理员权限，无法注册新用户！"));
    else{
        QString tablename=ui->comboBox->currentText();//当前选择的表名
        QSqlQuery query;
        query.exec("describe "+tablename);
        Insert* insertDi=new Insert(this);
        insertDi->init(query,tablename);
        insertDi->exec();
    }
    this->showData();
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
    bool res=query.exec(cmd);
    if(!res){
        QMessageBox::warning(this,tr("错误"),query.lastError().text());
    }
    this->showData();
}



void MainWindow::on_pushButton_4_clicked()
{
    if(!supremeUser){
         QMessageBox::warning(this,tr("错误"),tr("Lower User无法注册Supreme User"));
         return;
    }
    supremeUserRegister=true;
    Register* r=new Register(this);//要将r绑定到this上，否则内存泄漏，且关闭注册窗口，整个程序也退出了
    r->setWindowTitle("注册");
    r->exec();

}


void MainWindow::on_pushButton_5_clicked()
{
    supremeUserRegister=false;
    Register* r=new Register(this);
    r->setWindowTitle("注册");
    r->exec();
}


void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    this->showData();
}

void MainWindow::showData()
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


void MainWindow::on_pushButton_6_clicked()
{
    QString fileName=QFileDialog::getSaveFileName(this,tr("保存sql文件"),"D:",tr("sql文件(*sql)"));
    if(fileName.size()==0)return;
    QString cmd="mysqldump -u"+this->userName+" -p"+this->passWord+" server";
    QProcess p(this);
    p.setStandardOutputFile(fileName);
    p.start(cmd);
    p.waitForStarted();
    p.waitForFinished();
    QMessageBox::information(this,tr("提醒"),tr("导出完成！"),QMessageBox::Ok);
}

void MainWindow::getconfig(QString hostName, QString userName, QString passWord)
{
    this->hostName=hostName;
    this->userName=userName;
    this->passWord=passWord;
}

void MainWindow::on_pushButton_7_clicked()
{
    if(supremeUser||this->userName=="root"){
        QString fileName=QFileDialog::getOpenFileName(this,tr("导入sql文件"),"D:",tr("sql文件(*sql)"));
        if(fileName.size()==0)return;
        QString cmd="source "+fileName;
        QSqlQuery query;
        bool res=query.exec(cmd);
        if(res)QMessageBox::information(this,tr("提醒"),tr("导入完成！"),QMessageBox::Ok);
        else QMessageBox::warning(this,tr("错误"),tr("导入错误！"));
    }
    else QMessageBox::warning(this,tr("错误"),tr("权限不足，无法导入！"));
}

