#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "_qthread.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->send, &QPushButton::clicked, this, &MainWindow::on_send_clicked);
    //全局线程的创建
    connect(&m_heart,&QTimer::timeout, this, &MainWindow::timeout);
    m_heart.setInterval(100);
    m_thread = new _Thread(this);
    m_heart.start();
}

MainWindow::~MainWindow()
{

//    m_thread->stopImmediately();//由于此线程的父对象是Widget，因此退出时需要进行判断
    m_thread->wait();
    delete ui;

}


void MainWindow::on_send_clicked()
{
    std::cout << "std" << std::endl;
}

void MainWindow::timeout()
{
    static int s_heartcnt = 0;
    ++s_heartcnt;
    if(s_heartcnt >100)
    {
        s_heartcnt = 0;
    }
}

void MainWindow::on_connect_clicked()
{
    if(m_thread->isRunning())
    {
        return;
    }
    m_thread->start();
}
