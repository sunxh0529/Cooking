#include "figuredialog.h"
#include "ui_figuredialog.h"

figureDialog::figureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::figureDialog)
{
    ui->setupUi(this);
}

figureDialog::~figureDialog()
{
    delete ui;
}
