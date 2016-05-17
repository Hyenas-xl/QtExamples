#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "pieitem.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QVector<PieItem> items,bool showRate = false,QWidget *parent = 0);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *);

private:
    void draw(QPainter *painter,QRectF &rect,QColor &color,int startAngle,int spanAngle);

    void drawPolygon(QPainter *painter,QPointF topLeft,QPointF topRight);

    void drawText(QPainter *painter,int startAngle,int spanAngle,double rate=0);

    QPointF loadPoint(int angle) const;

    QVector<PieItem> items;

    QRectF rectTop = QRectF(10.0,20.0,280.0,160.0);
    QRectF rectBottom = QRectF(10.0,60.0,280.0,160.0);
    bool _showRate;
};

#endif // WIDGET_H
