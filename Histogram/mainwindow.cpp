#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "histogram.h"
#include "histogrammodel.h"
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    HistogramModel *model = new HistogramModel();
    QVector<HistogramModelItem> *items = new QVector<HistogramModelItem>;

    HistogramModelItem item1("测试数据一",Qt::red,4500.00);
    items->append(item1);

    HistogramModelItem item2("测试数据二",Qt::green,4000.01);
    items->append(item2);

    HistogramModelItem item3("测试数据三",Qt::blue,3000.6);
    items->append(item3);

    HistogramModelItem item4("测试数据四",Qt::black,1000.15);
    items->append(item4);

    HistogramModelItem item5("测试数据五",Qt::yellow,4800.15);
    items->append(item5);

    model->setData(items);

    histogram = new Histogram;
    histogram->setDrawYLine("测试值",true);
    histogram->setDrawValueLine(false);
    histogram->setModel(model);

    setCentralWidget(histogram);
}

MainWindow::~MainWindow()
{
    delete ui;
}
