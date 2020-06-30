#include "figurewidget.h"
#include "ui_figurewidget.h"

FigureWidget::FigureWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FigureWidget)
{
    ui->setupUi(this);
}

FigureWidget::~FigureWidget()
{
    delete ui;
}
