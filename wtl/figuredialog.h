#ifndef FIGUREDIALOG_H
#define FIGUREDIALOG_H

#include <QDialog>

namespace Ui {
class figureDialog;
}

class figureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit figureDialog(QWidget *parent = nullptr);
    ~figureDialog();

private:
    Ui::figureDialog *ui;
};

#endif // FIGUREDIALOG_H
