#include "closablewidget.h"
#include <QHBoxLayout>

ClosableWidget::ClosableWidget(QWidget *parent) : QWidget(parent){
    QHBoxLayout *layout = new QHBoxLayout;
    this->setLayout(layout);
    this->setFixedWidth(100);

    CustomizeButton *closeButton = new CustomizeButton(this);
    closeButton->setFlat(true);
    QIcon icon_close_1(":image/image/close1.png");
    QIcon icon_close_2(":image/image/close2.png");
    closeButton->setIcons(icon_close_1,icon_close_2);
    closeButton->setIconSize(QSize(20,20));
    closeButton->setToolTip(tr("Close"));

    maxButton = new CustomizeButton(this);
    maxButton->setFlat(true);
    icon_max_1 = QIcon(":image/image/max1.png");
    icon_max_2 = QIcon(":image/image/max2.png");
    icon_retore_1 = QIcon(":image/image/restore1.png");
    icon_retore_2 = QIcon(":image/image/restore2.png");
    maxButton->setIcons(icon_max_1,icon_max_2);
    maxButton->setIconSize(QSize(20,20));
    maxButton->setToolTip(tr("Max"));

    CustomizeButton *minButton = new CustomizeButton(this);
    minButton->setFlat(true);
    QIcon icon_min_1(":image/image/min1.png");
    QIcon icon_min_2(":image/image/min2.png");
    minButton->setIcons(icon_min_1,icon_min_2);
    minButton->setIconSize(QSize(20,20));
    minButton->setToolTip(tr("Min"));

    layout->addWidget(minButton);
    layout->addWidget(maxButton);
    layout->addWidget(closeButton);


    connect(closeButton,SIGNAL(clicked(bool)),this,SIGNAL(closeApplication()));
    connect(maxButton,SIGNAL(clicked(bool)),this,SIGNAL(maximizeOrRestore()));
    connect(minButton,SIGNAL(clicked(bool)),this,SIGNAL(minimize()));
}
void ClosableWidget::setFullScreen(bool full){
    if(full){
        maxButton->setIcons(icon_retore_1,icon_retore_2);
    }else{
        maxButton->setIcons(icon_max_1,icon_max_2);
    }
}

