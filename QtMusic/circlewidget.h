#ifndef CIRCLEWIDGET_H
#define CIRCLEWIDGET_H

#include <QLabel>

class CircleWidget : public QLabel
{
    Q_OBJECT
public:
    explicit CircleWidget(QString picture = NULL,QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *event);

signals:

public slots:
private:
    QPixmap *source;
};

#endif // CIRCLEWIDGET_H
