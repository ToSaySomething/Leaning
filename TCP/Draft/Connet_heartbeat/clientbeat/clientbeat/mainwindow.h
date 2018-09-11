#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "_qthread.h"
#include <QMainWindow>
#include <QTimer>
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
    void on_send_clicked();

//    void onQThreadFinished();
//    void progress(int val);
    void timeout();
    void on_connect_clicked();

private:
    Ui::MainWindow *ui;
    _Thread* m_thread;
    QTimer m_heart;
};

#endif // MAINWINDOW_H
