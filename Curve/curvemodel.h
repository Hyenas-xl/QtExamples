#ifndef CURVEMODEL_H
#define CURVEMODEL_H

#include <QObject>
#include <QVector>
#include <QColor>
#include "curvemodelitem.h"

class CurveModel : public QObject
{
    Q_OBJECT
public:
    explicit CurveModel(QObject *parent = 0);

    void setItems(QVector<CurveModelItem> *items);

    void append(CurveModelItem item);

    CurveModelItem item(int x) const;

    int itemCount() const;

    double maxValue() const;

    double minValue() const;

    void setColor(const QColor &color);

    QColor color() const;

    void refresh();
private:
    QVector<CurveModelItem> *items=0;
    double value_max=0;
    double value_min=0;
    QColor _color=Qt::black;
};

#endif // CURVEMODEL_H
