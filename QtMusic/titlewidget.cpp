#include "titlewidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include "imagetool.h"

TitleWidget::TitleWidget(QWidget *parent) : MovableWidget(parent)
{
    closableWidget = new ClosableWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(this);
    this->setLayout(layout);

    QLabel *label = new QLabel(this);
    QPixmap pixmap(":image/image/icon.png");
    getRoundPixmap(pixmap);
    label->setPixmap(pixmap.scaled(40,40,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

    layout->addWidget(label);
    layout->addStretch();
    layout->addWidget(closableWidget,Qt::AlignRight);

    connect(closableWidget,SIGNAL(closeApplication()),this,SIGNAL(closeApplication()));
    connect(closableWidget,SIGNAL(maximizeOrRestore()),this,SIGNAL(maximizeOrRestore()));
    connect(closableWidget,SIGNAL(minimize()),this,SIGNAL(minimize()));
}

void TitleWidget::setFullScreen(bool full){
    closableWidget->setFullScreen(full);
}

void TitleWidget::mouseDoubleClickEvent(QMouseEvent *){
    emit doubleClickTitle();
}
