#include "ClockWidget.h"
#include <QTimer>
#include <QTime>
#include <QtMath>
#include <QPainter>
ClockWidget::ClockWidget(QWidget *parent)
    : QWidget(parent)
{

    // ���춨ʱ�������ó�ʱΪ 1 ��
       QTimer *timer = new QTimer(this);
       connect(timer, SIGNAL(timeout()), this, SLOT(update()));
       timer->start(1000);

}

ClockWidget::~ClockWidget()
{
}

QRectF ClockWidget::textRectF(double radius, int pointSize, double angle)
{
    QRectF rectF;
    rectF.setX(radius*qCos(angle* M_PI/180.0) - pointSize*2);
    rectF.setY(radius*qSin(angle* M_PI/180.0) - pointSize/2.0);
    rectF.setWidth(pointSize*4);
    rectF.setHeight(pointSize);
    return rectF;
}

void ClockWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    // ʱ�롢���롢����λ�� - �����
    static const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -30)
    };
    static const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -65)
    };

    static const QPoint secondHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -80)
    };

    // ʱ�롢���롢������ɫ
    QColor hourColor(200, 100, 0, 200);
    QColor minuteColor(0, 127, 127, 150);
    QColor secondColor(0, 160, 230, 150);

    int side = qMin(width(), height());
    QTime time = QTime::currentTime();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // ƽ������ϵԭ�������ĵ�
    painter.translate(width() / 2, height() / 2);
    // ����
    painter.scale(side / 200.0, side / 200.0);

    // ����ʱ��
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);

    painter.save();
    // ÿȦ360�� = 12h ������ת�Ƕ� = Сʱ�� * 30��
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();

    painter.setPen(hourColor);

    // ����Сʱ�� ��360�� / 12 = 30�ȣ�
    for (int i = 0; i < 12; ++i) {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }

    int radius = 100;
    QFont font = painter.font();
    font.setBold(true);
    painter.setFont(font);
    int pointSize = font.pointSize();

    // ����Сʱ�ı�
    int nHour = 0;
    for (int i = 0; i < 12; ++i) {
        nHour = i + 3;
        if (nHour > 12)
            nHour -= 12;
        painter.drawText(textRectF(radius*0.8, pointSize, i * 30), Qt::AlignCenter, QString::number(nHour));
    }

    // ���Ʒ���
    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);

    painter.save();
    // ÿȦ360�� = 60m ������ת�Ƕ� = ������ * 6��
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();

    painter.setPen(minuteColor);

    // ���Ʒ����� ��360�� / 60 = 6�ȣ�
    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0);
    }

    // ��������
    painter.setPen(Qt::NoPen);
    painter.setBrush(secondColor);

    painter.save();
    // ÿȦ360�� = 60s ������ת�Ƕ� = ���� * 6��
    painter.rotate(6.0 * time.second());
    painter.drawConvexPolygon(secondHand, 3);
    painter.restore();
}

///NOTE::���Ϻܶ��ı���������ת֮�������ȥ�ģ�Ч�������ã�6 ��ʾ���� 9���������������һ�㣡
