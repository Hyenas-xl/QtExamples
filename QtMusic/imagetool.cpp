#include "imagetool.h"
#include <QPainter>
#include <QBitmap>
#include <QDebug>

void brightnessChanged(QImage &image,int brightness){
    uchar *line = image.scanLine(0);
    uchar *pix;
    for(int i=0;i < image.height();i++){
        pix = line;
        for(int j=0;j < image.width();j++){
            *pix = qBound(0,*pix+brightness,255);
            *(pix+1) = qBound(0,*(pix+1)+brightness,255);
            *(pix+2) = qBound(0,*(pix+2)+brightness,255);
            pix += 4;
        }
        line += image.bytesPerLine();
    }
}

void getRoundPixmap(QPixmap &source){
    QSize size(source.size());
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(mask.rect(),Qt::white);
    painter.setBrush(QColor(0,0,0));
    int radius = size.width()/2;
    painter.drawRoundRect(mask.rect(),radius,radius);

    source.setMask(mask);
}
