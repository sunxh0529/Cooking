#ifndef COMMANDWIDGET_H
#define COMMANDWIDGET_H

#include <QWidget>

namespace Ui {
class CommandWidget;
}

class CommandWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommandWidget(QWidget *parent = nullptr);
    ~CommandWidget();

private:
    Ui::CommandWidget *ui;
};

#endif // COMMANDWIDGET_H
