#include "movablewidget.h"
#include <QMouseEvent>

MovableWidget::MovableWidget(QWidget *parent) : QWidget(parent){

}

void MovableWidget::mouseMoveEvent(QMouseEvent *event){
    if(m_press){
        emit widgetMove(event->pos()-m_point);
    }
}

void MovableWidget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        m_press = true;
        m_point = event->pos();
    }
}

void MovableWidget::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event);
    m_press = false;
}
