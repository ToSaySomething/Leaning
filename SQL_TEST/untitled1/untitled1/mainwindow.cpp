#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newdialog.h"
#include "SqlOper.h"
#include "qstring.h"
#include "BaseObj.h"
#include "ProductObj.h"
#include "Tool.h"
#include "Server.h"
#include <QMetaType>
#include "Serialization.pb.h"
#include "ProtoToolHelper.h"
#include "string.h"
#include <QMessageBox>

using std::string;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType<string>("string");
    connect(Tool::tool_signal, SIGNAL(toolSignalOpen(string)), this, SLOT(showMsg(string)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(checkPort())
        server.openServer(ui->lineEdit->text().toStdString());
    else{
        QMessageBox box(QMessageBox::Critical,"Wrong","Please input between 1 and 65536");
        box.exec();
    }

//    table::ProductObj *p_obj = new table::ProductObj(1,"ads",23);
//    p_obj->setId(1);
//    p_obj->setName("ads");
//    p_obj->setValue(23);
//    Tool::showMsgOnMainWindow("send ProjectObj:\nid:"+Tool::intToString(p_obj->getId())+
//                                            "\nname:"+p_obj->getName()+
//                                            "\nvalue:"+Tool::intToString(p_obj->getValue())+
//                                            "\ntable:"+p_obj->getTableName()+"\n");
//    CmdData cd;
//    if(ProtoToolHelper::setCmdData(p_obj,CmdData::INSERT,cd,"ProductObj"))
//        Tool::showMsgOnMainWindow("setCmdData Success\n");
//    else Tool::showMsgOnMainWindow("setCmdData Fail\n");
//    string pstr = ProtoToolHelper::CmdDataToString(cd);
//    Tool::showMsgOnMainWindow("CmdDataToString.....");
//    if(pstr == "")
//        Tool::showMsgOnMainWindow("Fail\n");
//    CmdData cd_2 = ProtoToolHelper::StringToCmdData(pstr);

//    table::ProductObj* p_obj2 = static_cast<table::ProductObj*>(ProtoToolHelper::getBaseObj(cd_2));
//    Tool::showMsgOnMainWindow("/nsend ProjectObj:\nid:"+Tool::intToString(p_obj2->getId())+
//                                            "\nname:"+p_obj2->getName()+
//                                            "\nvalue:"+Tool::intToString(p_obj2->getValue())+
//                                            "\ntable:"+p_obj2->getTableName()+"\n"
//                                            );


}

void MainWindow::on_pushButton_2_clicked()
{
//    newDialog *dlg = new newDialog;
//    connect(dlg, SIGNAL(sendData(int,string,int)), this, SLOT(button2Act(int,string,int)), Qt::DirectConnection);
//    dlg->show();
}


void MainWindow::button2Act(int id,string name,int value){
//    table::BaseObj *p = getPtrFromValue(id,name,value);
//    string result = Db::SqlOper::insertData(p);
//    ui->textBrowser->insertPlainText(QString::fromStdString(result));
//    result = Db::SqlOper::selectData(p)+"\n\n";
//    ui->textBrowser->insertPlainText(QString::fromStdString(result));
}


void MainWindow::on_pushButton_3_clicked()
{
//    newDialog *dlg = new newDialog;
//    connect(dlg, SIGNAL(sendData(int,string,int)), this, SLOT(button3Act(int,string,int)));
//    dlg->show();
}

void MainWindow::button3Act(int id,string name,int value){
//    table::BaseObj *p = getPtrFromValue(id,name,value);
//    string result = Db::SqlOper::updateData(p);
//    ui->textBrowser->insertPlainText(QString::fromStdString(result));
//    result = Db::SqlOper::selectData(p)+"\n\n";
//    ui->textBrowser->insertPlainText(QString::fromStdString(result));
}




void MainWindow::on_pushButton_4_clicked()
{
//    Produc
}

void MainWindow::button4Act(int id,string name,int value){
//    table::BaseObj *p = getPtrFromValue(id,name,value);
//    string result = Db::SqlOper::deleteData(p);
//    ui->textBrowser->insertPlainText(QString::fromStdString(result));
//    result = Db::SqlOper::selectData(p)+"\n\n";
//    ui->textBrowser->insertPlainText(QString::fromStdString(result));
}

SharedPtr<table::BaseObj> MainWindow::getPtrFromValue(int a, string b, int c){
//    table::BaseObj *p = new table::ProductObj(a,b,c);
//    return p;
}

void MainWindow::showMsg(string msg){
    ui->textBrowser->insertPlainText(QString::fromStdString(msg));
}

bool MainWindow::checkPort(){
    QString pattern("[0-9]{1,5}");
    QRegExp rx(pattern);
    QString text = ui->lineEdit->text();
    bool match = rx.exactMatch(text);
    if(!match)
        return false;
    if(text.toInt()>=0&&text.toInt()<256*256)
        return true;
    else return false;
}
