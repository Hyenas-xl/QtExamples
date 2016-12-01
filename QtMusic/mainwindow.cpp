#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QListWidget>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new MusciPlayer;

    titleWidget = new TitleWidget(ui->centralWidget);
    titleWidget->setAutoFillBackground(true);
    titleWidget->setPalette(QColor(45,195,124));
    titleWidget->setFixedHeight(60);

    bottomWidget = new BottomWidget(ui->centralWidget);
    bottomWidget->setAutoFillBackground(true);
    bottomWidget->setPalette(QColor(45,46,48));
    bottomWidget->setFixedHeight(60);

    centorWidget = new CentorWdiget(ui->centralWidget);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    ui->centralWidget->setLayout(layout);

    layout->addWidget(titleWidget);
    layout->addWidget(centorWidget);
    layout->addWidget(bottomWidget);

    connect(titleWidget,SIGNAL(widgetMove(QPoint)),this,SLOT(widgetMove(QPoint)));
    connect(bottomWidget,SIGNAL(widgetMove(QPoint)),this,SLOT(widgetMove(QPoint)));

    connect(titleWidget,SIGNAL(closeApplication()),this,SLOT(close()));
    connect(titleWidget,SIGNAL(minimize()),this,SLOT(showMinimized()));
    connect(titleWidget,SIGNAL(maximizeOrRestore()),this,SLOT(maximizeOrRestore()));
    connect(titleWidget,SIGNAL(doubleClickTitle()),this,SLOT(maximizeOrRestore()));

    connect(player,SIGNAL(durationChanged(qint64)),bottomWidget,SLOT(durationChanged(qint64)));
    connect(player,SIGNAL(positionChanged(qint64)),bottomWidget,SLOT(positionChanged(qint64)));
    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),bottomWidget,SLOT(stateChanged(QMediaPlayer::State)));
    connect(bottomWidget,SIGNAL(playOrPauseSong()),player,SLOT(playMusic()));
    connect(bottomWidget,SIGNAL(setPostion(int)),player,SLOT(setPostion(int)));
    connect(bottomWidget,SIGNAL(previousSong()),player,SLOT(previousSong()));
    connect(bottomWidget,SIGNAL(nextSong()),player,SLOT(nextSong()));

    connect(centorWidget,SIGNAL(changPlayMenu(QString,QVector<QUrl>&)),player,SLOT(changeMenu(QString,QVector<QUrl>&)));
    connect(centorWidget,SIGNAL(addSong(QUrl,int)),player,SLOT(addSong(QUrl,int)));
    connect(centorWidget,SIGNAL(playMusic(int)),player,SLOT(playMusicByIndex(int)));
    connect(centorWidget,SIGNAL(playingMenu()),this,SLOT(checkMenu()));

    connect(player,SIGNAL(currentIndexChanged(int)),this,SLOT(changeSong(int)));

    centorWidget->initMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkMenu(){
    centorWidget->songName(player->menuName(),player->currentIndex());
}

void MainWindow::changeSong(int index){
    QString name[2];
    centorWidget->changeMenu(player->menuName());
    centorWidget->songName(player->menuName(),index,name);
    bottomWidget->setPlayingName(name[0],name[1]);
}

void MainWindow::widgetMove(QPoint movePoint){
    this->move(movePoint+this->pos());
}

void MainWindow::maximizeOrRestore(){
    if(this->isMaximized()){
        this->showNormal();
        this->show();
        titleWidget->setFullScreen(false);
    }else{
        this->showMaximized();
        titleWidget->setFullScreen(true);
    }
}
