#ifndef PIEITEM_H
#define PIEITEM_H

#include <QObject>
#include <QColor>
class PieItem
{
public:
    PieItem(QString name,QColor color,double value);

    PieItem();

    void setName(QString name);

    void setColor(QColor color);

    void setValue(double value);

    QString name() const;

    QColor color() const;

    double value() const;

private:
    QString _name;
    QColor _color;
    double _value=0;
};

#endif // PIEITEM_H
