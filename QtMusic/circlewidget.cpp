#include "circlewidget.h"
#include <QPainter>
#include <QRadialGradient>
#include "imagetool.h"

CircleWidget::CircleWidget(QString picture,QWidget *parent) : QLabel(parent)
{
    source = new QPixmap(picture);
    getRoundPixmap(*source);
    setPixmap(*source);
}

void CircleWidget::mousePressEvent(QMouseEvent *){

}

void CircleWidget::paintEvent(QPaintEvent *event){
//    QPainter *painter = new QPainter(this);
//    painter->setRenderHint(QPainter::Antialiasing);
//    painter->drawPixmap(rect(),*source);
//    painter->end();
    QWidget::paintEvent(event);
}

