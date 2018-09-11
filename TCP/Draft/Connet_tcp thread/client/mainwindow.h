#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myclient.h"
#include <QMainWindow>

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
    void display();

    int getport(){
        return ui_port;
    }
    char* getip(){
        return ui_ip;
    }
    void setip(char* ip){
        ui_ip = ip;
    }
    void setport(int port){
        ui_port = port;
    }



    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    MyClient myclient;
    char* ui_ip;
    int ui_port;
    QString re_QString;
};

#endif // MAINWINDOW_H
