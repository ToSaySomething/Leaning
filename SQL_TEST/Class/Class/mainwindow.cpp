#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mysql.h"
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

void MainWindow::on_pushButton_clicked()//create
{
    sql.init();
    //Session session("SQLite", "Sample.db");
    sql.create();
}

void MainWindow::on_pushButton_2_clicked() //insert
{
    //Session session("SQLite", "Sample.db");
//    Person person = {"An","101","111@qq.com"};
    Person person;
    //protobuf
    QString qstrname = ui->Name_->toPlainText();
    std::string strname = qstrname.toStdString();
    person.name = strname;

    QString qstrid =  ui->ID_->toPlainText();
    std::string strid = qstrid.toStdString();
    person.id = strid;

    QString qstremail = ui->Email_->toPlainText();
    std::string stremail = qstremail.toStdString();
    person.email = stremail;

    sql.insert(person);
}

void MainWindow::on_pushButton_3_clicked()//update
{
    Person person;
    QString qstrname = ui->Name_->toPlainText();
    std::string strname = qstrname.toStdString();
    person.name = strname;

    QString qstrid =  ui->ID_->toPlainText();
    std::string strid = qstrid.toStdString();
    person.id = strid;

    QString qstremail = ui->Email_->toPlainText();
    std::string stremail = qstremail.toStdString();
    person.id = stremail;

    //Session session("SQLite", "Sample.db");
    sql.update(person);
}


void MainWindow::on_pushButton_4_clicked()
{
    QString qstrname = ui->Name_->toPlainText();
    std::string strname = qstrname.toStdString();
    //Session session("SQLite", "Sample.db");
    sql.del(strname);
}

void MainWindow::on_pushButton_5_clicked() //display
{
    //Session session("SQLite", "Sample.db");
    struct Person person_[50];
    int cnt = sql.display(person_);
    //std::cout << person_[0].name << std::endl;

    std::string s = "Name  ID   Email \n";
    for(int i=0; i<cnt; i++)
    {
        s += person_[i].name + " " + person_[i].id+ " " + person_[i].id + "\n";
    }
    ui->textEdit->setPlainText(QString::fromStdString(s));
}

//        QString qstrname = QString::fromStdString(person_[i].name);
//        QString qstrid = QString::fromStdString(person_[i].id);
//        QString qstremail = QString::fromStdString(person_[i].email);
