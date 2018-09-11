#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include <QDialog>

using std::string;

namespace Ui {
class newDialog;
}

class newDialog : public QDialog
{
    Q_OBJECT

public:
    explicit newDialog(QWidget *parent = 0);
    ~newDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

signals:
    void sendData(int,string,int);

private:
    Ui::newDialog *ui;
};

#endif // NEWDIALOG_H
