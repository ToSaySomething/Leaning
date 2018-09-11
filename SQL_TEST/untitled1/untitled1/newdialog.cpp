#include "newdialog.h"
#include "ui_newdialog.h"

#include <iostream>

using std::string;

newDialog::newDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newDialog)
{
    ui->setupUi(this);
}

newDialog::~newDialog()
{
    delete ui;
}

void newDialog::on_buttonBox_accepted()
{
    QString buf = ui->lineEditID->text();
    int id = buf.toInt();
    std::cout<<id;
    buf = ui->lineEditName->text();
    string name = buf.toStdString();

    buf = ui->lineEditValue->text();
    int value = buf.toInt();

    emit sendData(id,name,value);
}

void newDialog::on_buttonBox_rejected()
{

}
