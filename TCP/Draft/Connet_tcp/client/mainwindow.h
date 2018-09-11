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

    int getport(){
        return port;
    }

    char* getip(){
        return ip;
    }

    void setip(char* _ip){
        ip = _ip;
    }

    void setport(int _port){
        port = _port;
    }



private:
    Ui::MainWindow *ui;
    MyClient myclient;
    char* ip;
    int port;
};

#endif // MAINWINDOW_H
