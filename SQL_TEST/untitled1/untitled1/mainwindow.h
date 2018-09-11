#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "BaseObj.h"
#include "ProductObj.h"
#include "Server.h"
#include "Poco/SharedPtr.h"

using std::string;
using Poco::SharedPtr;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void button2Act(int,string,int);

    void button3Act(int,string,int);

    void button4Act(int,string,int);

    SharedPtr<table::BaseObj> getPtrFromValue(int,string,int);

    void showMsg(string);



private:
    Ui::MainWindow *ui;
    Server server = Server();
    bool checkPort();

};

#endif // MAINWINDOW_H
