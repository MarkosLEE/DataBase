#include "register.h"
#include "ui_register.h"

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
    this->close();
}

