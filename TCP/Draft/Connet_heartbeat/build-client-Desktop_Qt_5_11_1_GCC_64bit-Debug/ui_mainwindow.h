/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QGroupBox *groupBox;
    QTextEdit *ID_;
    QTextEdit *Email_;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_2;
    QTextEdit *Name_;
    QPushButton *pushButton_4;
    QLabel *label;
    QTextEdit *Head_;
    QLabel *label_5;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(810, 403);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(50, 20, 61, 31));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(300, 110, 61, 31));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(180, 20, 61, 31));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(20, 100, 251, 51));
        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(20, 170, 251, 111));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(400, 100, 331, 231));
        ID_ = new QTextEdit(groupBox);
        ID_->setObjectName(QStringLiteral("ID_"));
        ID_->setGeometry(QRect(100, 110, 211, 31));
        Email_ = new QTextEdit(groupBox);
        Email_->setObjectName(QStringLiteral("Email_"));
        Email_->setGeometry(QRect(100, 170, 211, 31));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 170, 67, 17));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 110, 21, 21));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 60, 51, 17));
        Name_ = new QTextEdit(groupBox);
        Name_->setObjectName(QStringLiteral("Name_"));
        Name_->setGeometry(QRect(100, 60, 211, 31));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(300, 170, 61, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(420, 20, 67, 17));
        Head_ = new QTextEdit(centralWidget);
        Head_->setObjectName(QStringLiteral("Head_"));
        Head_->setGeometry(QRect(500, 10, 211, 31));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(420, 60, 321, 31));
        MainWindow->setCentralWidget(centralWidget);
        groupBox->raise();
        pushButton->raise();
        pushButton_2->raise();
        pushButton_3->raise();
        textEdit->raise();
        textEdit_2->raise();
        pushButton_4->raise();
        label->raise();
        Head_->raise();
        label_5->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 810, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "connect", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "send", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "close", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "People", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Email:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "ID:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Name:", nullptr));
        pushButton_4->setText(QApplication::translate("MainWindow", "receive", nullptr));
        label->setText(QApplication::translate("MainWindow", "operator", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "1:insert  2:delete  3:update  4:select  5 display", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
