#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mysql.h"
#include <QMainWindow>

using Poco::Data::Session;
using Poco::Data::Statement;




namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();//create

    void on_pushButton_2_clicked();//insert

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    MYSQL sql;
};

#endif // MAINWINDOW_H
