#include "chooseuser.h"
#include "ui_chooseuser.h"
extern bool rootuser;
ChooseUser::ChooseUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseUser)
{
    ui->setupUi(this);
}

ChooseUser::~ChooseUser()
{
    delete ui;
}

void ChooseUser::on_pushButton_2_clicked()
{
    rootuser=true;
    this->close();
}


void ChooseUser::on_pushButton_clicked()
{
    rootuser=false;
    this->close();
}

