/********************************************************************************
** Form generated from reading UI file 'newdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWDIALOG_H
#define UI_NEWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_newDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditValue;
    QLineEdit *lineEditName;
    QLineEdit *lineEditID;

    void setupUi(QDialog *newDialog)
    {
        if (newDialog->objectName().isEmpty())
            newDialog->setObjectName(QStringLiteral("newDialog"));
        newDialog->resize(400, 163);
        buttonBox = new QDialogButtonBox(newDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 120, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(newDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 21, 16));
        label_2 = new QLabel(newDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 50, 57, 14));
        label_3 = new QLabel(newDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 80, 57, 14));
        lineEditValue = new QLineEdit(newDialog);
        lineEditValue->setObjectName(QStringLiteral("lineEditValue"));
        lineEditValue->setGeometry(QRect(65, 75, 300, 25));
        lineEditName = new QLineEdit(newDialog);
        lineEditName->setObjectName(QStringLiteral("lineEditName"));
        lineEditName->setGeometry(QRect(65, 45, 300, 25));
        lineEditID = new QLineEdit(newDialog);
        lineEditID->setObjectName(QStringLiteral("lineEditID"));
        lineEditID->setGeometry(QRect(65, 15, 300, 25));

        retranslateUi(newDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), newDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), newDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(newDialog);
    } // setupUi

    void retranslateUi(QDialog *newDialog)
    {
        newDialog->setWindowTitle(QApplication::translate("newDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("newDialog", "ID", nullptr));
        label_2->setText(QApplication::translate("newDialog", "Name", nullptr));
        label_3->setText(QApplication::translate("newDialog", "Value", nullptr));
    } // retranslateUi

};

namespace Ui {
    class newDialog: public Ui_newDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWDIALOG_H
