#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QWidget>
#include <QtGui>
#include "histogrammodel.h"
#include "histogrammodelitem.h"

class Histogram : public QWidget
{
    Q_OBJECT

public:
    explicit Histogram(QWidget *parent = 0);
    ~Histogram();
    /**
     * @brief setModel
     * @param model 数据模型
     */
    void setModel(HistogramModel *model);
    /**
     * @brief 是否绘制item value line
     * @param draw
     */
    void setDrawValueLine(bool draw=true);
    /**
     * @brief 绘制y轴
     * @param draw
     */
    void setDrawYLine(const QString name,bool draw=false);
    /**
     * @brief 获取当前点所在item
     * @param point
     * @return
     */
    HistogramModelItem selectItem(QPoint &point) const;

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *);

private:
    HistogramModel *model=0;
    QMap<int,QRect> itemRects;

    int leftItem = 50;
    int rightItem = 100;
    int topItem = 20;
    int bottomItem = 60;
    int item_default_width = 30;
    int left_start = 20;

    bool drawValueLine = true;
    bool drawY = false;
    QString y_name;
};

#endif // HISTOGRAM_H
