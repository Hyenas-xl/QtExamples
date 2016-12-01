#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "titlewidget.h"
#include "bottomwidget.h"
#include "musciplayer.h"
#include "centorwdiget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void widgetMove(QPoint movePoint);
    void maximizeOrRestore();
    void changeSong(int index);
    void checkMenu();
private:
    Ui::MainWindow *ui;
    TitleWidget *titleWidget;
    BottomWidget *bottomWidget;
    CentorWdiget *centorWidget;
    MusciPlayer *player;
};

#endif // MAINWINDOW_H
