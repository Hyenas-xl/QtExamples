#include "curve.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>

Curve::Curve(const QString nameX,QString nameY,QWidget *parent)
    : QWidget(parent),x_name(nameX),y_name(nameY)
{

}

void Curve::setMaxScale(double value){
    this->maxScale = value;
}

void Curve::addModel(CurveModel *model){
    models.append(model);
}

void Curve::paintEvent(QPaintEvent *){
    if(models.size() == 0){
        return;
    }

    QPixmap *pixmap = new QPixmap(size());
    pixmap->fill(Qt::white);

    QSize rect = frameSize();
    QPainter *painter = new QPainter;

    int width = rect.width();
    int height = rect.height();

    QPoint originPoint(leftItem,height-bottomItem);
    QPoint leftTopPoint(leftItem,topItem);
    QPoint rightBottomPoint(rect.width()-rightItem,height-bottomItem);

    painter->begin(pixmap);
    painter->setRenderHint(QPainter::Antialiasing,true);
    QFont font("Arial",8,QFont::Normal);
    painter->setFont(font);

    //y
    painter->drawLine(leftTopPoint,originPoint);
    painter->drawText(QRect(leftItem-10,topItem-16,40,16),Qt::AlignLeft,y_name);

    models.at(0)->refresh();
    double maxValue = maxScale > 0.0 ? maxScale : models.at(0)->maxValue();
    int maxY = originPoint.y() - leftTopPoint.y() - 10;
    int maxX = rightBottomPoint.x() - originPoint.x()-10;
    //y 刻度
    int scaleStandard = calculateScale(maxValue);
    int scaleNum = qCeil(maxValue/scaleStandard);
    int scaleValue = maxY/scaleNum;
    int totalValue = scaleStandard*scaleNum;
    for(int i=0;i <= scaleNum;i++){
        int scale = scaleValue*i;
        if(i > 0){
            painter->drawLine(leftItem-4,originPoint.y()-scale,leftItem,originPoint.y()-scale);
            painter->drawText(QRect(0,originPoint.y()-scale-8,leftItem-6,16),Qt::AlignRight,QString::number(i*scaleStandard));
        }
        for(int j=1;j < 5;j++){
            int _scale = j*(scaleValue/5);
            painter->drawLine(leftItem-2,originPoint.y()-scale-_scale,leftItem,originPoint.y()-scale-_scale);
        }
    }

    //x 刻度
    int size = models.at(0)->itemCount();
    int num = (size>=50 && size <100)?5 : (size >=100? 10:1);
    scaleValue = maxX/size;
    QVector<QPoint> points;
    for(int i=0;i < size;i++){
        CurveModelItem _item = models.at(0)->item(i);
        int scale = (i+1)*scaleValue;
        painter->drawLine(originPoint.x()+scale,originPoint.y(),originPoint.x()+scale,originPoint.y()-4);
        if((i+1)%num == 0){
            painter->drawText(originPoint.x()+scale-4,originPoint.y()+15,_item.x());
        }
        int yvalue = qFloor((_item.y()/totalValue)*maxY);
        points.append(QPoint(originPoint.x()+scale,originPoint.y()-yvalue));
        xmap.insert(_item.x(),originPoint.x()+scale);
    }

    size = points.size()-1;
    for(int i=0; i < size;i++){
        QPoint p1 = points.at(i);
        QPoint p2 = points.at(i+1);
        painter->setPen(QPen(models.at(0)->color()));
        painter->drawLine(p1,p2);
    }

    //多条曲线
    if(models.size() > 1){
        for(int j=1;j < models.size();j++){
            points.clear();
            models.at(j)->refresh();
            size = models.at(j)->itemCount();
            for(int i=0;i < size;i++){
                CurveModelItem _item = models.at(j)->item(i);
                int x = xmap.take(_item.x());
                int yvalue = qFloor((_item.y()/totalValue)*maxY);
                points.append(QPoint(x,originPoint.y()-yvalue));
            }
            size = points.size()-1;
            for(int i=0; i < size;i++){
                QPoint p1 = points.at(i);
                QPoint p2 = points.at(i+1);
                painter->setPen(QPen(models.at(j)->color()));
                painter->drawLine(p1,p2);
            }
        }
    }

    //x
    painter->setPen(Qt::black);
    painter->drawLine(originPoint,rightBottomPoint);
    painter->drawText(QRect(width-rightItem+4,height-bottomItem-8,40,16),Qt::AlignLeft,x_name);
    painter->end();

    QPainter painterMain(this);
    painterMain.drawPixmap(QPoint(0,0),*pixmap);
}

int Curve::calculateScale(double value){
    int data = (int)value;
    int scale = 1;
    do{
        scale *= 10;
    } while((data/scale) > 0);
    return scale/10;
}
