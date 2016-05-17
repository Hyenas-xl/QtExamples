#include "pieitem.h"

PieItem::PieItem(QString name,QColor color,double value):
    _name(name),_color(color),_value(value){
}

PieItem::PieItem(){}

void PieItem::setColor(QColor color){
    this->_color = color;
}

void PieItem::setName(QString name){
    this->_name = name;
}
void PieItem::setValue(double value){
    this->_value = value;
}

QString PieItem::name() const{
    return _name;
}
QColor PieItem::color() const{
    return _color;
}
double PieItem::value() const{
    return _value;
}
