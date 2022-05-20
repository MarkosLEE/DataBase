#ifndef INSERT_H
#define INSERT_H

#include <QDialog>
#include<QSqlQuery>
#include<QLineEdit>
namespace Ui {
class Insert;
}

class Insert : public QDialog
{
    Q_OBJECT

public:
    explicit Insert(QWidget *parent = nullptr);
    void init(QSqlQuery query,QString tablename);//初始化插入数据窗口
    ~Insert();

private slots:
    void on_pushButton_2_clicked();
    //这个地方遇到了一个问题，就是不能往里面传参数，因为这会破坏结构
    //如果想传参数，则要自己写connect函数

    void on_pushButton_clicked();

private:
    Ui::Insert *ui;
    QLineEdit*input=nullptr;//输入数据的文本框
    QString tablename;//表名
    QSqlQuery query;//传入的表结构
};

#endif // INSERT_H
