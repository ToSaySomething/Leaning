#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mysql.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sql1.init();
    Session session("SQLite", "Sample.db");

    Person person = {"An","xx","111"};
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString nameString = ui->lineEdit->text();
    QString telString = ui->lineEdit_2->text();
    QString ageString = ui->lineEdit_3->text();
    Person person;
    person.name = nameString;
    person.tel = telString;
    person.age = ageString;
    sql1.insert(person, session);
    QMessageBox::about(NULL, "About", "successful insert");
}
