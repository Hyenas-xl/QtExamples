#include "mouseslider.h"
#include <QMouseEvent>

MouseSlider::MouseSlider(QWidget *parent) : QSlider(parent){

}
MouseSlider::MouseSlider(Qt::Orientation orientation,QWidget *parent) : QSlider(orientation,parent){

}

void MouseSlider::mousePressEvent(QMouseEvent *event){
    QSlider::mousePressEvent(event);
    double pos = event->pos().x() / (double)width();
    int value = (maximum()-minimum())*pos + minimum();
    emit sliderMoved(value);
}
