#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    void onfigure_longinBtn_clicked();
    void oncommand_loginBtn_clicked();
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
};


#endif // DIALOG_H
