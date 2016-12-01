#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include "movablewidget.h"
#include "closablewidget.h"

class TitleWidget : public MovableWidget
{
    Q_OBJECT
public:
    explicit TitleWidget(QWidget *parent = 0);
    void setFullScreen(bool full);

protected:
    void mouseDoubleClickEvent(QMouseEvent *);

signals:
    void closeApplication();
    void maximizeOrRestore();
    void minimize();
    void doubleClickTitle();

public slots:

private:
    ClosableWidget *closableWidget;
};

#endif // TITLEWIDGET_H
