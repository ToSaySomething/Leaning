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


void MainWindow::on_pushButton_clicked() //connect
{
    char* ip = "127.0.0.1";
    setip(ip);
    int port = 9000;
    setport(port);

    int t = 510;
    while(t--)
    {
        myclient.myconnect(ip, port);
    }
    std::cout << "end" << std::endl;

}

void MainWindow::on_pushButton_3_clicked() //close
{
    myclient.close();
}

void MainWindow::on_pushButton_2_clicked() //send
{
    QString str =  ui->textEdit->toPlainText();
    std::string strsend = str.toStdString();
    QString reQString = myclient.send( strsend );
    re_QString = reQString;
    display();
}

void MainWindow::on_pushButton_4_clicked() //receive
{
    QString reQString = myclient.receive();
    re_QString = reQString;
    display();
}

void MainWindow::display()
{
    if(re_QString.isEmpty())
    {
        std::cout << "client: rev error" << std::endl;
        return ;
    }
    // receive server inform
    ui->textEdit_2->setPlainText(re_QString);

    //display:name id email
    std::string str1 = re_QString.toStdString();
    people::People p;
    p.ParseFromString(str1);

    //display
    ui->textEdit_3->setPlainText( QString::fromStdString( p.name() ) );
    ui->textEdit_4->setPlainText( QString::fromStdString( p.id() ) );
    ui->textEdit_5->setPlainText( QString::fromStdString( p.email() ) );
}

