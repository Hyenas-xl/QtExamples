#include "histogrammodel.h"

HistogramModel::HistogramModel(){

}

HistogramModel::HistogramModel(QString namex,QString namey,QObject *parent)
    : QObject(parent),x_name(namex),y_name(namey){

}
HistogramModel::HistogramModel(const HistogramModel &model){
    this->x_name = model.x_name;
    this->y_name = model.y_name;
    this->items = model.items;
}

HistogramModel::~HistogramModel(){

}

int HistogramModel::itemsCount() const{
    if(NULL != items){
        return items->size();
    }
    return 0;
}

void HistogramModel::setData(QVector<HistogramModelItem> *items) {
    this->items = items;
}

void HistogramModel::append(HistogramModelItem item){
    if(NULL == items){
        items = new QVector<HistogramModelItem>;
    }
    items->append(item);
}

HistogramModelItem HistogramModel::item(int index) const{
    if(NULL != items && index < items->size()){
        return items->at(index);
    }
    return HistogramModelItem();
}
HistogramModelItem HistogramModel::item(QString name) const{
    if(NULL != items){
        QVector<HistogramModelItem>::const_iterator i;
        for(i=items->constBegin();i != items->constEnd();i++){
            if(0 == i->name().compare(name,Qt::CaseInsensitive)){
                return *i;
            }
        }
    }
}
QString HistogramModel::nameX() const{
    return x_name;
}
QString HistogramModel::nameY() const{
    return y_name;
}

double HistogramModel::maxValue() const{
    double value = 0;
    if(NULL != items){
        QVector<HistogramModelItem>::const_iterator i;
        for(i=items->constBegin();i != items->constEnd();i++){
            double _value = i->data();
            if(value < _value){
                value = _value;
            }
        }
    }
    return value;
}
