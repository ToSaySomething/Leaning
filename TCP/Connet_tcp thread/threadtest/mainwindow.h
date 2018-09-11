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
    void on_pushButton_clicked();
    void timeout();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    _Thread* m_thread;
    QTimer m_heart;
};

#endif // MAINWINDOW_H
