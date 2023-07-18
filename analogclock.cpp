#include "analogclock.h"
#include "./ui_analogclock.h"
#include <QPainter>
#include <QTime>
#include <QTimer>
analogclock::analogclock(QWidget *parent)
    : QWidget(parent)
{
    QTimer* timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,QOverload<>::of(&analogclock::update));
    timer->start(1000);
    setWindowTitle(tr("Стрілковий годинник"));
    resize(500,500);
    setStyleSheet("background-color:black");
}

analogclock::~analogclock()
{
    delete ui;
}

void analogclock::paintEvent(QPaintEvent *){
    static const QPoint hourHand[4]={
        QPoint(3,-20),
        QPoint(0,0),
        QPoint(-3,-20),
        QPoint(0,-60)

    };
    static const QPoint minuteHand[4]={
        QPoint(4,-30),
        QPoint(0,0),
        QPoint(-4,-30),
        QPoint(0,-80)

    };
    static const QPoint secondHand[3]={
        QPoint(1,8),
        QPoint(-1,8),
        QPoint(0,-80),
    };

    QColor hourColor(25,255,255);
    QColor minuteColor(255,200,0);
    QColor secondColor(255,0,0);
    QColor circleColor(255,0,0);
    QColor dotColor(255,255,255);
    int side = qMin(width(),height());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width()/2,height()/2);
    painter.scale(side/200.0,side/200.0);

    QTime time = QTime::currentTime();

    QFont font;
    font.setPixelSize(6);
    painter.setFont(font);
    painter.setPen(hourColor);
    for(int i = 0; i<24; ++i){

            painter.drawLine(85,0,96,0);
        painter.rotate(15.0);

    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(secondColor);
    painter.save();
    painter.rotate(6.0*(time.second()));
    painter.drawConvexPolygon(secondHand,3);
    painter.restore();

    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);
    painter.save();
    painter.rotate(6.0*(time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand,4);
    painter.restore();
    painter.setPen(dotColor);
    for(int i = 0; i<60; ++i){
        if((i%5) != 0)
            painter.drawLine(95,0,96,0);
        painter.rotate(6.0);

    }
    qreal hourAngle = 360.0 * (time.msecsSinceStartOfDay() / (24.0 * 60.0 * 60.0 * 1000.0));
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);
    painter.save();
    painter.rotate(hourAngle);
    painter.drawConvexPolygon(hourHand,4);
    painter.restore();
    painter.setPen(secondColor);

}
