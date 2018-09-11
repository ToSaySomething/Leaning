#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myclient.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{   //connect
    char* _ip = "127.0.0.1";
    setip(_ip);
    int _port = 9000;
    setport(_port);

    myclient.myconnect(_ip, port);

}

void MainWindow::on_pushButton_3_clicked()
{   //close
    //shutdown();

}

void MainWindow::on_pushButton_2_clicked()
{
    //send
    QString str =  ui->textEdit->toPlainText();
    std::string strsend = str.toStdString();

    QString reQString = myclient.send(getip(), getport(), strsend);
    // receive server inform
   // QString reQString = QString::fromStdString(reString);
    ui->textEdit_2->setPlainText(reQString);



}



