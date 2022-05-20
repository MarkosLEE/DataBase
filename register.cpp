#include"global.h"
extern bool supremeUserRegister;
Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}
//这个槽函数里面还需要一个函数来判断密码是否合法，用户名是否已经存在，若都符合则关闭窗口
void Register::on_pushButton_clicked()
{
    if(ui->LineEdit_3->text()!=ui->LineEdit_4->text()){
        QMessageBox::warning(this,tr("错误"),tr("密码不一致，请重新输入！"));
    }
    QSqlQuery Register;
    QString cmd="create user '"+ui->LineEdit->text()+"'@'"+ui->LineEdit_2->text()+"'identified with caching_sha2_password by'"+ui->LineEdit_3->text()+"'";
    Register.exec(cmd);
    cmd="grant create user on *.* to '"+ui->LineEdit->text()+"'@'"+ui->LineEdit_2->text()+"' with grant option";
    Register.exec(cmd);

    cmd="grant select on server.* to '"+ui->LineEdit->text()+"'@'"+ui->LineEdit_2->text()+"' with grant option";
    Register.exec(cmd);

    cmd="grant update on server.server_has_player to '"+ui->LineEdit->text()+"'@'"+ui->LineEdit_2->text()+"' with grant option";
    Register.exec(cmd);

    cmd="grant update on server.team_has_player to '"+ui->LineEdit->text()+"'@'"+ui->LineEdit_2->text()+"' with grant option";
    Register.exec(cmd);
    if(supremeUserRegister){
         cmd="grant insert,update,delete on server.server to '"+ui->LineEdit->text()+"'@'"+ui->LineEdit_2->text()+"' with grant option";
         Register.exec(cmd);

         cmd="grant insert,update,delete on server.player to '"+ui->LineEdit->text()+"'@'"+ui->LineEdit_2->text()+"' with grant option";
         Register.exec(cmd);

         cmd="grant insert,update,delete on server.domainname to '"+ui->LineEdit->text()+"'@'"+ui->LineEdit_2->text()+"' with grant option";
         Register.exec(cmd);
    }


    this->close();
}

