#include "widget.h"
#include <QApplication>
#include "pieitem.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QVector<PieItem> items;
    items.append(PieItem("item1",Qt::red,3));
    items.append(PieItem("item2",Qt::green,2));
    items.append(PieItem("item3",Qt::yellow,1));
    items.append(PieItem("item4",Qt::blue,20));
    items.append(PieItem("item5",Qt::magenta,11));
    items.append(PieItem("item6",Qt::cyan,10));

    Widget w(items,true);
    w.show();

    return a.exec();
}
