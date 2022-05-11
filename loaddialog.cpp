#include "loaddialog.h"
#include "ui_loaddialog.h"
#include "register.h"
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
    accept();
}


void LoadDialog::on_pushButton_2_clicked()
{
    Register* r=new Register;
    r->setWindowTitle("注册");
    r->exec();
}

