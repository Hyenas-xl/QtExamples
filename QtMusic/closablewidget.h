#ifndef CLOSABLEWIDGET_H
#define CLOSABLEWIDGET_H

#include <QWidget>
#include "customizebutton.h"

class ClosableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ClosableWidget(QWidget *parent = 0);

    void setFullScreen(bool full);

signals:
    void closeApplication();
    void maximizeOrRestore();
    void minimize();
private:
    CustomizeButton *maxButton = 0;
    QIcon icon_max_1;
    QIcon icon_max_2;
    QIcon icon_retore_1;
    QIcon icon_retore_2;
};

#endif // CLOSABLEWIDGET_H
