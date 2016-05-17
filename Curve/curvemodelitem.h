#ifndef CURVEMODELITEM_H
#define CURVEMODELITEM_H

#include <QObject>

class CurveModelItem
{

public:
    CurveModelItem();

    CurveModelItem(const QString x,double y);

    void setX(const QString x);
    void setY(double y);

    QString x() const;
    double y() const;

    bool isValid() const;

private:
    QString _x;
    double _y=0;
};

#endif // CURVEMODELITEM_H
