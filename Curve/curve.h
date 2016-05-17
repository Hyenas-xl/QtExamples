#ifndef CURVE_H
#define CURVE_H

#include <QWidget>
#include <QtGui>
#include "curvemodel.h"

class Curve : public QWidget
{
    Q_OBJECT
public:
    explicit Curve(const QString nameX,QString nameY,QWidget *parent = 0);

    void setMaxScale(double value);

    void addModel(CurveModel *model);

    int calculateScale(double value);

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    int leftItem = 50;
    int rightItem = 50;
    int topItem = 20;
    int bottomItem = 60;

    double maxScale=0.0;
    QString y_name;
    QString x_name;

    QVector<CurveModel*> models;
    QMap<QString,int> xmap;
};

#endif // CURVE_H
