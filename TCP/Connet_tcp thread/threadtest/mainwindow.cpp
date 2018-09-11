#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);

    //全局线程
    connect(&m_heart,&QTimer::timeout, this, &MainWindow::timeout);
    m_heart.setInterval(1000);
    m_thread = new _Thread(this);
    m_heart.start();
}

MainWindow::~MainWindow()
{
    m_thread->wait();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    m_thread->Something();
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

void MainWindow::on_pushButton_2_clicked()
{

    if(m_thread->isRunning())
    {
        return;
    }
    m_thread->start();
}
