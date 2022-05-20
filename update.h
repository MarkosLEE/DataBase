#ifndef UPDATE_H
#define UPDATE_H

#include <QDialog>
#include<QSqlQuery>
#include<QLineEdit>
#include<QSqlQueryModel>
namespace Ui {
class update;
}

class update : public QDialog
{
    Q_OBJECT

public:
    explicit update(QWidget *parent = nullptr);
    ~update();
    void init(QString name,QSqlQueryModel*model,int row);
    void init(QSqlQuery query,QString tablename,QSqlQueryModel*model,int row);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::update *ui;
    QLineEdit*input=nullptr;//输入数据的文本框
    QString tablename;//表名
    QSqlQuery query;//传入的表结构
    QSqlQueryModel*model;
    int row;//当前选中的行号
};

#endif // UPDATE_H
