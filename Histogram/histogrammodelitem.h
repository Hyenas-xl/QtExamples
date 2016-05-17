#ifndef HISTOGRAMMODELITEM_H
#define HISTOGRAMMODELITEM_H

#include <QObject>
#include <QColor>
#include <QVector>

class HistogramModelItem
{

public:
    HistogramModelItem();

    HistogramModelItem(QString name,QColor color,double data);

    ~HistogramModelItem();

    void setData(double data);

    void setName(QString name);

    void setColor(QColor color);

    double data() const;

    QString name() const;

    QColor color() const;

    bool isValid() const;

signals:

public slots:

private:
    QString _name;
    QColor _color;
    double _data;
    bool valid;
};

#endif // HISTOGRAMMODELITEM_H
