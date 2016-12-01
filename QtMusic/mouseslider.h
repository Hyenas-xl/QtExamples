#ifndef MOUSESLIDER_H
#define MOUSESLIDER_H

#include <QSlider>
class MouseSlider : public QSlider
{
public:
    MouseSlider(QWidget *parent = 0);
    explicit MouseSlider(Qt::Orientation orientation, QWidget *parent = Q_NULLPTR);

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // MOUSESLIDER_H
