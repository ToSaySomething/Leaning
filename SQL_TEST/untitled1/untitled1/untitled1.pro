#-------------------------------------------------
#
# Project created by QtCreator 2018-07-17T02:42:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    SqlOper.cpp \
    newdialog.cpp \
    ProductObj.cpp \
    BaseObj.cpp \
    ServerConnection.cpp \
    Server.cpp \
    ServerConnectionFactory.cpp \
    ProtoToolHelper.cpp \
    Serialization.pb.cc \
    DbOperNotification.cpp \
    DbOperThread.cpp \
    StreamSockectNotification.cpp \
    SendMsgThread.cpp \
    Tool.cpp

HEADERS  += mainwindow.h \
    SqlOper.h \
    newdialog.h \
    BaseObj.h \
    ProductObj.h \
    ServerConnection.h \
    Tool.h \
    Server.h \
    ServerConnectionFactory.h \
    ProtoToolHelper.h \
    Serialization.pb.h \
    DbOperNotification.h \
    DbOperThread.h \
    StreamSockectNotification.h \
    SendMsgThread.h

FORMS    += mainwindow.ui \
    newdialog.ui

LIBS = -lPocoUtil -lPocoXML -lPocoNet -lPocoFoundation -lPocoJSON -lPocoData -lPocoDataSQLite -lprotobuf -pthread
