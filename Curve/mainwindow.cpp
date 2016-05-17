#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "curve.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(600,300);
    Curve *curve = new Curve("x轴","y轴");
    CurveModel *model = new CurveModel;
//    model->append(CurveModelItem("一",9));
//    model->append(CurveModelItem("二",10));
//    model->append(CurveModelItem("三",12));
//    model->append(CurveModelItem("四",14));
//    model->append(CurveModelItem("五",15));
//    model->append(CurveModelItem("六",13));
//    model->append(CurveModelItem("七",10));
//    model->append(CurveModelItem("八",8));
//    model->append(CurveModelItem("九",3));
    for(int i=0;i < 100;i++){
        model->append(CurveModelItem(QString::number(i+1),10+qrand()%10));
    }
    model->setColor(Qt::red);

    CurveModel *model2 = new CurveModel;
//    model2->append(CurveModelItem("一",8));
//    model2->append(CurveModelItem("二",10));
//    model2->append(CurveModelItem("三",11));
//    model2->append(CurveModelItem("四",12));
//    model2->append(CurveModelItem("五",13));
//    model2->append(CurveModelItem("六",12));
//    model2->append(CurveModelItem("七",11));
//    model2->append(CurveModelItem("八",10));
//    model2->append(CurveModelItem("九",9));
    for(int i=0;i < 30;i++){
        model2->append(CurveModelItem(QString::number(i+1),10+qrand()%10));
    }
    model2->setColor(Qt::blue);

    curve->addModel(model);
    curve->addModel(model2);

    setCentralWidget(curve);
}

MainWindow::~MainWindow()
{
    delete ui;
}
