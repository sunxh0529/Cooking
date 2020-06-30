#include "widget.h"
#include "logindialog.h"
#include <QApplication>

#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.show();

//    LoginDialog w_dlg;
//    if (w_dlg.exec() == QDialog::Accepted)
//    {
//        qDebug()<<"成功输入用户名和密码";
//    }
//    {
//        w.show();
//        return a.exec();
//    }
//    else return 0;



    return a.exec();
}
