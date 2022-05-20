#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtSql/QSqlDatabase>
#include<QSqlQueryModel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init();//初始化函数，用来读取数据库有多少表，并添加到combox中
    void getconfig(QString hostName,QString userName,QString passWord);
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void showData();//显示表数据
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();
    void on_comboBox_currentIndexChanged(const QString &arg1);


    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel*model;
    QString hostName;//主机名
    QString userName;//用户名
    QString passWord;//密码
};
#endif // MAINWINDOW_H
