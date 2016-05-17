#include "curvemodel.h"

CurveModel::CurveModel(QObject *parent) : QObject(parent){
}

void CurveModel::setItems(QVector<CurveModelItem> *items){
    this->items = items;
}

void CurveModel::append(CurveModelItem item){
    if(NULL == items){
        items = new QVector<CurveModelItem>;
    }
    items->append(item);
}

CurveModelItem CurveModel::item(int x) const{
    if(NULL != items && x < items->size()){
        return items->at(x);
    }
    return CurveModelItem();
}

int CurveModel::itemCount() const{
    if(NULL != items){
        return items->size();
    }
    return 0;
}

void CurveModel::refresh(){
     if(NULL != items){
         int size = itemCount();
         for(int i=0;i < size;i++){
             CurveModelItem _item = item(i);
             if(_item.isValid()){
                 if(_item.y() > value_max){
                     value_max = _item.y();
                 }
                 if(_item.y() < value_min){
                     value_min = _item.y();
                 }
             }
         }
     }
}

double CurveModel::maxValue() const{
    return value_max;
}
double CurveModel::minValue() const{
    return value_min;
}
void CurveModel::setColor(const QColor &color){
    this->_color = color;
}
QColor CurveModel::color() const{
    return _color;
}
