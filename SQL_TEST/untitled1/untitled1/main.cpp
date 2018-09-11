#include "mainwindow.h"
#include <QApplication>
#include "Poco/SharedPtr.h"

#include "Tool.h"

using Poco::SharedPtr;

ToolSignal::ToolSignal(QObject *parent):QObject(parent){}

SharedPtr<ToolSignal> Tool::tool_signal = new ToolSignal;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
