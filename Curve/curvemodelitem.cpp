#include "curvemodelitem.h"

CurveModelItem::CurveModelItem(){
}

CurveModelItem::CurveModelItem(const QString x, double y){
    this->_x = x;
    this->_y = y;
}
void CurveModelItem::setX(const QString x){
    this->_x = x;
}

void CurveModelItem::setY(double y){
    this->_y = y;
}
QString CurveModelItem::x() const{
    return _x;
}
double CurveModelItem::y() const{
    return _y;
}

bool CurveModelItem::isValid() const{
    return !_x.isEmpty();
}
