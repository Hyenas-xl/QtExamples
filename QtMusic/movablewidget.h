#ifndef MOVABLEWIDGET_H
#define MOVABLEWIDGET_H

#include <QWidget>

class MovableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MovableWidget(QWidget *parent = 0);

protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    bool m_press = false;
    QPoint m_point;

signals:
    void widgetMove(QPoint point);
};

#endif // MOVABLEWIDGET_H
