#ifndef FIGUREWIDGET_H
#define FIGUREWIDGET_H

#include <QWidget>

namespace Ui {
class FigureWidget;
}

class FigureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FigureWidget(QWidget *parent = nullptr);
    ~FigureWidget();

private:
    Ui::FigureWidget *ui;
};

#endif // FIGUREWIDGET_H
