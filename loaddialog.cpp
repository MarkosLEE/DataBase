#include"global.h"
extern QSqlDatabase db;
extern bool supremeUser;
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
    db.setDatabaseName("Server");//数据库名
    db.setUserName(username);//管理员用户
    db.setPassword(password);//此处填入对应的用户密码
    bool ok=db.open();
    if(ok){
        this->close();
        isSupreme(username);
        MainWindow *rootMainWindow=new MainWindow(this);
        rootMainWindow->getconfig(hostname,username,password);
        rootMainWindow->init();
        rootMainWindow->show();
    }
    else{
        QMessageBox::warning(this,tr("错误"),tr("连接数据库失败，请检查用户名、主机名以及密码是否正确"));
    }
}




void LoadDialog::isSupreme(QString userName){
    QSqlQuery query;
    query.exec("show grants for '"+userName+"'@'localhost'");
    if(query.size()<=4&&userName!="root")supremeUser=false;
    else supremeUser=true;
}

