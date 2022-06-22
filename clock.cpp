#include "clock.h"

#include <QPainter>
#include <QTime>
#include <QTimer>

Clock::Clock(QWidget *parent)
    : QMainWindow(parent)

{
    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Clock::update));

    timer->start(1000);

    setWindowTitle(tr("Clock"));
    resize(400, 400);
}

void Clock::paintEvent(QPaintEvent *)

{
    static const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -40)
    };
    static const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };
    static const QPoint secondHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -90)
    };

    QColor hourColor(35, 196, 133);
    QColor minuteColor(187, 143, 206);
    QColor secondColor(109, 125, 207);

    int side = qMin(width(), height());
    QTime time = QTime::currentTime();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);
    painter.setOpacity(0.6);

    painter.save();
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();

    painter.setPen(hourColor);


    for (int i = 0; i < 12; ++i) {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }


    painter.setPen(Qt::NoPen);

    painter.setBrush(minuteColor);
    painter.setOpacity(0.4);


    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();


    painter.setPen(minuteColor);
    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0);
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(secondColor);
    painter.setOpacity(0.2);

    painter.save();
    painter.rotate(6.0 * (time.second() + time.msec() / 1000.0));
    painter.drawConvexPolygon(secondHand, 3);
    painter.restore();
    painter.setPen(secondColor);
    for (int k = 0; k < 60; k++){
        if((k % 5) != 0)
            //painter.drawLine(84, 0, 96, 0);
        painter.rotate(1.0);
    }

}


