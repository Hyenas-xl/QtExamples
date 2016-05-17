#include "widget.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#define PI 3.1415926

Widget::Widget(QVector<PieItem> items,bool showRate,QWidget *parent)
    : QWidget(parent){

    this->items = items;
    this->_showRate = showRate;
}

Widget::~Widget()
{
    if(!items.isEmpty()){
        items.clear();
    }
}

QPointF Widget::loadPoint(int angle) const{
    double dwidth = rectTop.width() * 0.5 * cos(angle*PI/180);
    double dheight = rectTop.height() * 0.5 * sin(angle*PI/180);

    double dx = rectTop.center().x() + dwidth + 0.5;
    double dy = rectTop.center().y() - dheight + 0.5;
    return QPointF(dx,dy);
}

void Widget::draw(QPainter *painter, QRectF &rect, QColor &color,int startAngle,int spanAngle){
    double _startAngle = startAngle * 16;
    if(rect == rectTop){
        painter->setBrush(color.dark());
        QPointF topRight = loadPoint(startAngle+spanAngle);
        QPointF topLeft = loadPoint(startAngle);
        if(topLeft.y() > rectTop.center().y() || topRight.y() > rectTop.center().y()){
            drawPolygon(painter,topLeft,topRight);
        }

        painter->setBrush(color);
        painter->drawPie(rectTop, _startAngle, spanAngle * 16);
    }else{
        painter->setBrush(color.dark());
        painter->drawPie(rectBottom,_startAngle,spanAngle*16);
    }
}

void Widget::drawText(QPainter *painter, int startAngle, int spanAngle, double rate){
    QPointF mid = loadPoint(startAngle+spanAngle/2);
    double midx = (mid.x() > rectTop.center().x()) ? mid.x()-100*rate : mid.x()+100*rate;
    double midy = (mid.y() > rectTop.center().y()) ? mid.y()-10 : mid.y()+10;
    painter->drawText(QRectF(midx,midy,40,10),QString::number(rate*100,'f',2).append("%"));
}

void Widget::drawPolygon(QPainter *painter, QPointF topLeft, QPointF topRight){
    qreal spanY = rectBottom.y() - rectTop.y();

    if(topLeft.y() < rectTop.center().y()){
        topLeft = rectTop.center() + QPointF(-rectTop.width()*0.5,0);
    }
    if(topRight.y() < rectTop.center().y()){
        topRight = rectTop.center() + QPointF(rectTop.width()*0.5,0);
    }
    QPointF bottomLeft = topLeft + QPointF(0,spanY);
    QPointF BottomRight = topRight + QPointF(0,spanY);
    QPolygonF path;
    path << topLeft << topRight << BottomRight << bottomLeft;
    painter->drawPolygon(path);
}

void Widget::paintEvent(QPaintEvent *ev){
    QPainter *painter = new QPainter(this);

    //反锯齿
    painter->setRenderHint(QPainter::Antialiasing);

    QVector<PieItem>::const_iterator start;
    double totalValue=0;
    int left = rectTop.x()+rectTop.width()+30;
    int top = rectTop.y();
    painter->setPen(Qt::black);
    QSize _size = frameSize();
    for(start=items.constBegin();start != items.constEnd();start++){
        totalValue += start->value();
        QColor color = start->color();
        QString name = start->name();
        painter->setBrush(color);
        painter->drawRect(left,top,10,10);
        painter->drawText(QRectF(left+15,top,_size.width()-left-15,10),name);
        top += 15;
    }

    painter->setPen(Qt::NoPen);
    double startAngle = 90;
    for(start=items.constBegin();start != items.constEnd();start++){
        QColor color = start->color();
        double value = start->value();
        int angle = (int)360 *value/totalValue;
        draw(painter,rectBottom,color,startAngle,angle);
        startAngle = startAngle + angle;
    }
    startAngle = 90;
    for(int i=0;i < items.size();i++){
        PieItem item = items.at(i);
        QColor color = item.color();
        double value = item.value();
        int angle = (int)360*value/totalValue;
        if(i == items.size()-1){
            //浮点数计算丢失精度
            angle = (360+90)-startAngle;
        }
        draw(painter,rectTop,color,startAngle,angle);
        startAngle = startAngle + angle;
    }
    if(_showRate){
        painter->setPen(Qt::black);
        for(start=items.constBegin();start != items.constEnd();start++){
            double value = start->value();
            int angle = (int)360 *value/totalValue;
            double rate = value/totalValue;
            drawText(painter,startAngle,angle,rate);
            startAngle = startAngle + angle;
        }
    }
    painter->end();
    QWidget::paintEvent(ev);
}
