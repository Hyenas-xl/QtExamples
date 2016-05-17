#include "histogrammodelitem.h"

HistogramModelItem::HistogramModelItem(){
    valid = false;
}

HistogramModelItem::HistogramModelItem(QString name,QColor color,double data){
    this->valid = true;
    this->_name = name;
    this->_color = color;
    this->_data = data;
}
HistogramModelItem::~HistogramModelItem(){

}

void HistogramModelItem::setData(double data){
    this->_data = data;
}
void HistogramModelItem::setName(QString name){
    this->_name = name;
}
void HistogramModelItem::setColor(QColor color){
    this->_color = color;
}
double HistogramModelItem::data() const{
    return _data;
}
QString HistogramModelItem::name() const{
    return _name;
}
QColor HistogramModelItem::color() const{
    return _color;
}
bool HistogramModelItem::isValid() const{
    return valid;
}
