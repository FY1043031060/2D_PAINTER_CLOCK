#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>

class ClockWidget : public QWidget
{
    Q_OBJECT

    QRectF textRectF(double radius, int pointSize, double angle);
public:
    ClockWidget(QWidget *parent = nullptr);
    ~ClockWidget();
    void paintEvent(QPaintEvent *event);
};
#endif // CLOCKWIDGET_H
