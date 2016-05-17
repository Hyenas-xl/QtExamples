#ifndef HISTOGRAMMODEL_H
#define HISTOGRAMMODEL_H

#include <QObject>
#include "histogrammodelitem.h"

class HistogramModel : public QObject
{
    Q_OBJECT
public:
    HistogramModel();
    HistogramModel(QString namex,QString namey,QObject *parent=0);
//    HistogramModel &operator =(const HistogramModel &model);
    HistogramModel(const HistogramModel & model);

    ~HistogramModel();
    /**
     * @brief 获取元素个数
     * @return
     */
    int itemsCount() const;

    void setData(QVector<HistogramModelItem> *items);

    void append(HistogramModelItem item);

    HistogramModelItem item(QString name) const;

    HistogramModelItem item(int index) const;

    void setCoordinateNames(QVector<QString> *names);

    double maxValue() const;

    QString nameX() const;
    QString nameY() const;

private:
    QVector<HistogramModelItem> *items=0;
    QString x_name;
    QString y_name;
};

#endif // HISTOGRAMMODEL_H
