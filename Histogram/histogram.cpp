#include "histogram.h"
#include <QPixmap>
#include <QPainter>
#include <QPoint>
#include <QDebug>
#include <QLinearGradient>
#include <QMouseEvent>

Histogram::Histogram(QWidget *parent) :
    QWidget(parent){
}

Histogram::~Histogram(){

}
void Histogram::setModel(HistogramModel *model){
    this->model = model;
}

void Histogram::setDrawValueLine(bool draw){
    this->drawValueLine = draw;
}

void Histogram::setDrawYLine(const QString name,bool draw){
    this->drawY = draw;
    this->y_name = name;
}

HistogramModelItem Histogram::selectItem(QPoint &point) const{
    if(itemRects.size() > 0 && NULL != model && model->itemsCount() > 0){
        QMap<int,QRect>::const_iterator r;
        for(r = itemRects.constBegin(); r != itemRects.constEnd();r++){
            if(r.value().contains(point)){
                return model->item(r.key());
            }
        }
    }
    return HistogramModelItem();
}

void Histogram::paintEvent(QPaintEvent *){
    if(NULL == model){
        return;
    }
    itemRects.clear();
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white));

    QPixmap *pixmap = new QPixmap(size());
    pixmap->fill(Qt::white);

    QSize rect = frameSize();
    QPainter *painter = new QPainter;

    int width = rect.width();
    int height = rect.height();

    QPoint originPoint(leftItem,height-bottomItem);
    QPoint leftTopPoint(leftItem,topItem);
    QPoint rightBottomPoint(width-rightItem,height-bottomItem);

    painter->begin(pixmap);
    painter->setRenderHint(QPainter::Antialiasing,true);

    if(NULL != model && model->itemsCount() > 0){
        model->nameX();
        model->nameY();
        int size = model->itemsCount();
        int xwidth = rightBottomPoint.x() - originPoint.x();
        int itemWidth = 0;
        if(size > 1){
            itemWidth = (xwidth - 2*left_start - item_default_width*size)/(size -1);
        }else{
            itemWidth = (xwidth - item_default_width)/2;
        }

        int maxY = originPoint.y() - leftTopPoint.y() - 10;
        double maxValue = model->maxValue();
        QFont font("Arial",8,QFont::Normal);
        painter->setFont(font);

        if(drawY){
            painter->drawLine(leftTopPoint,originPoint);
            painter->drawText(QRect(leftItem-10,topItem-16,40,16),Qt::AlignRight,y_name);
            int yScaleValue = int(maxValue/5);
            int yScale = maxY/5;
            for(int i=1;i <= 5;i++){
                int scale = yScale*i;
                painter->drawLine(leftItem-4,originPoint.y()-scale,leftItem,originPoint.y()-scale);
                painter->drawText(QRect(0,originPoint.y()-scale-8,leftItem-6,16),Qt::AlignRight,QString::number(i*yScaleValue));
            }
        }

        if(drawValueLine){
            for(int i=0;i < size;i++){
                HistogramModelItem item = model->item(i);
                if(!item.isValid()){
                    continue;
                }

                double value = item.data();
                int yheight = int(maxY*(value/maxValue));
                painter->setPen(QPen(Qt::black));

                if(drawValueLine){
                    painter->drawLine(leftItem,originPoint.y()-yheight,width-rightItem,originPoint.y()-yheight);
                    painter->drawText(QRect(0,originPoint.y()-yheight-8,leftItem-5,16),Qt::AlignRight,QString::number(value));
                    painter->drawText(QRect(width-rightItem+5,originPoint.y()-yheight-8,rightItem-5,16),Qt::AlignLeft,QString::number(value));
                }
            }
        }

        for(int i=0;i < size;i++){
            HistogramModelItem item = model->item(i);
            double value = item.data();
            QColor color = item.color();
            QString name = item.name();

            painter->setPen(QPen(color));
            int yheight = int(maxY*(value/maxValue));
            int leftx = originPoint.x()+left_start+i*(itemWidth+item_default_width);

            QPoint _leftTop(leftx,originPoint.y()-yheight);
            QPoint _rightBottom(leftx+item_default_width,originPoint.y()-1);

            QLinearGradient linearGradient(leftx,originPoint.y()-yheight/2,leftx+item_default_width,originPoint.y()-yheight/2);
            linearGradient.setColorAt(0,color);
            linearGradient.setColorAt(0.5,Qt::white);
            linearGradient.setColorAt(1,color);
            painter->setBrush(QBrush(linearGradient));
            QRect _rect(_leftTop,_rightBottom);
            itemRects.insert(i,_rect);
            painter->drawRect(_rect);

            painter->setPen(QPen(Qt::black));
            painter->drawText(leftx,originPoint.y()+15,name);
        }
    }

    painter->setPen(QPen(Qt::black));
    //x
    painter->drawLine(originPoint,rightBottomPoint);
    painter->end();

    QPainter painterMain(this);
    painterMain.drawPixmap(QPoint(0,0),*pixmap);
}

void Histogram::mousePressEvent(QMouseEvent *event){
    QPoint p = event->pos();
    HistogramModelItem _item = selectItem(p);
    if(_item.isValid()){
        qDebug() << "select item{"<<"name:"<<_item.name()<<",value:"<<_item.data()<<"}";
    }else{
        qDebug()<<"Item inValid.";
    }
}
