#include "widget.h"
#include "ui_widget.h"
#include "schedule.h"
#include "travelerplan.h"
#include "mypushbutton.h"
#include "logindialog.h"
#include "ui_logindialog.h"

#include <QDebug>
#include <QIcon>
#include <QPainter>
#include <QDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowIcon(QPixmap(":/sxh/res/logo-1.png"));
    this->setFixedSize(800,600);
    this->setWindowTitle("模拟旅行风险计划");


    //开始按钮
    MyPushButton * startBtn = new MyPushButton(":/sxh/res/button.png");
    startBtn->setParent(this);
    startBtn->move( this->width() * 0.5 - startBtn->width() * 0.5,this->height() * 0.95 - startBtn->height() * 0.5);
    connect(startBtn,&MyPushButton::clicked,[=](){
        //实现弹跳
        startBtn->zoom1();
        startBtn->zoom2();
        this->hide();

        //登录用户名和密码
        LoginDialog dlg(this);
        dlg.resize(100,233);
        dlg.exec();

    });


//    Schedule *database = new Schedule;
//    TravelerPlan *Traveler = new TravelerPlan(0, QDateTime(QDate(2020,6,27),QTime(9,0)),
//                         QDateTime(QDate(2021,6,27),QTime(9,0)), 0, Schedule::CityToNum("Beijing"),
//                          Schedule::CityToNum("Shenzhen"));

}

void Widget::paintEvent(QPaintEvent *)
{
    //创建画家，指定绘图设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/sxh/res/pic-1.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}

Widget::~Widget()
{
    delete ui;
}
