#include "logindialog.h"
#include "ui_logindialog.h"
#include "figurewidget.h"
#include "commandwidget.h"
#include "widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QTimer>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    connect(ui->figureBtn,&QPushButton::clicked,this,&LoginDialog::onfigure_longinBtn_clicked);
    connect(ui->commandBtn,&QPushButton::clicked,this,&LoginDialog::oncommand_loginBtn_clicked);
}

void LoginDialog::oncommand_loginBtn_clicked()
{
    //判断用户名和密码是否正确，错误弹出警示对话框
    if (ui->usrLineEdit->text() == tr("sxh") && ui->pwdLineEdit->text() == tr("123456"))
    {
        CommandWidget * comwidget = new CommandWidget;

        connect(ui->loginBtn,&QPushButton::clicked,[=](){
            QTimer::singleShot(200, this,[=](){
                this->hide();//隐藏登录对话框
                comwidget->show();
            });
        });


    }
    else QMessageBox::warning(this,tr("警告！"),tr("用户名或者密码错误！"),QMessageBox::Yes);
}

void LoginDialog::onfigure_longinBtn_clicked()
{
    //判断用户名和密码是否正确，错误弹出警示对话框
    if (ui->usrLineEdit->text() == tr("sxh") && ui->pwdLineEdit->text() == tr("123456"))
    {
        FigureWidget * figwidegt = new FigureWidget;

        connect(ui->loginBtn,&QPushButton::clicked,[=](){
            QTimer::singleShot(200, this,[=](){
                this->hide();//隐藏登录对话框
                figwidegt->show();
            });
        });
    }
    else QMessageBox::warning(this,tr("警告！"),tr("用户名或者密码错误！"),QMessageBox::Yes);

}



LoginDialog::~LoginDialog()
{
    delete ui;
}
