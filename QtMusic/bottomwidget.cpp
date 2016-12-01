#include "bottomwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

BottomWidget::BottomWidget(QWidget *parent) : MovableWidget(parent){

    QWidget *playWidget = new QWidget(this);
    this->initPalyButtons(playWidget);

    QWidget *scheduleWidget = new QWidget(this);
    this->initScheduleBar(scheduleWidget);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(10);
//    layout->setMargin(2);
    this->setLayout(layout);

    layout->addWidget(playWidget);
    layout->addWidget(scheduleWidget);
}

void BottomWidget::initPalyButtons(QWidget *parent){
    parent->setFixedSize(130,40);
    CustomizeButton *leftButton = new CustomizeButton(parent);
    leftButton->setFlat(true);
    QIcon icon_left_1(":image/image/leftButton1.png");
    QIcon icon_left_2(":image/image/leftButton2.png");
    leftButton->setIcons(icon_left_1,icon_left_2);
    leftButton->setIconSize(QSize(40,40));
    leftButton->setToolTip(tr("上一首"));
    leftButton->setFixedSize(40,40);

    palyButton = new CustomizeButton(parent);
    palyButton->setFlat(true);
    QIcon icon_play_1(":image/image/playButton1.png");
    QIcon icon_play_2(":image/image/playButton2.png");
    palyButton->setIcons(icon_play_1,icon_play_2);
    palyButton->setIconSize(QSize(40,40));
    palyButton->setToolTip(tr("播放"));
    palyButton->setFixedSize(40,40);

    CustomizeButton *rightButton = new CustomizeButton(parent);
    rightButton->setFlat(true);
    QIcon icon_right_1(":image/image/rightButton1.png");
    QIcon icon_right_2(":image/image/rightButton2.png");
    rightButton->setIcons(icon_right_1,icon_right_2);
    rightButton->setIconSize(QSize(40,40));
    rightButton->setToolTip(tr("下一首"));
    rightButton->setFixedSize(40,40);

    QHBoxLayout *layout = new QHBoxLayout(parent);
    layout->setMargin(0);
    layout->setSpacing(5);
    parent->setLayout(layout);

    layout->addWidget(leftButton);
    layout->addWidget(palyButton);
    layout->addWidget(rightButton);

    connect(leftButton,SIGNAL(clicked(bool)),this,SIGNAL(previousSong()));
    connect(palyButton,SIGNAL(clicked(bool)),this,SIGNAL(playOrPauseSong()));
    connect(rightButton,SIGNAL(clicked(bool)),this,SIGNAL(nextSong()));
}

void BottomWidget::initScheduleBar(QWidget *parent){
    QWidget *scheduleTextWidget = new QWidget(parent);
    scheduleTextWidget->setPalette(Qt::green);
    scheduleTextWidget->setFixedHeight(15);
    QHBoxLayout *scheduleTextLayout = new QHBoxLayout(scheduleTextWidget);
    scheduleTextWidget->setLayout(scheduleTextLayout);
    scheduleTextLayout->setMargin(0);

    musicName1 = new QLabel(scheduleTextWidget);
    QPalette namePalette;
    namePalette.setColor(QPalette::WindowText,QColor(170,170,170));
    musicName1->setPalette(namePalette);

    musicName2 = new QLabel(scheduleTextWidget);
    QPalette palette;
    palette.setColor(QPalette::WindowText,QColor(120,120,120));
    musicName2->setPalette(palette);

    musicTime = new QLabel(scheduleTextWidget);
    musicTime->setPalette(palette);
    scheduleTextLayout->setMargin(0);
    scheduleTextLayout->addWidget(musicName1);
    scheduleTextLayout->addWidget(musicName2);
    scheduleTextLayout->addStretch();
    scheduleTextLayout->addWidget(musicTime);

    slider = new MouseSlider(Qt::Horizontal,parent);
    slider->setFixedHeight(5);
    slider->setStyleSheet(""
                          "QSlider::add-page:Horizontal{background-color: rgb(87, 97, 106);height:4px;}"
                          "QSlider::sub-page:Horizontal{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), stop:1 rgba(7,208,255, 255));height:4px;}"
                          "QSlider::groove:Horizontal{background:transparent;height:6px;}"
                          "QSlider::handle:Horizontal{height: 30px;width:8px;margin: -8 0px;}");

    QVBoxLayout *scheduleLayout = new QVBoxLayout(parent);
    scheduleLayout->setSpacing(20);
    scheduleLayout->setMargin(10);
    parent->setLayout(scheduleLayout);
    scheduleLayout->addWidget(scheduleTextWidget);
    scheduleLayout->addWidget(slider);

    connect(slider,SIGNAL(sliderMoved(int)),this,SIGNAL(setPostion(int)));
}

void BottomWidget::setPlayingName(QString songName,QString author){
    if(musicName1 && !songName.isEmpty()){
        musicName1->setText(songName);
    }
    if(musicName2 && !author.isEmpty()){
        musicName2->setText("- "+author);
    }
}

void BottomWidget::stateChanged(QMediaPlayer::State state){
    if(state == QMediaPlayer::PlayingState){
        QIcon icon_play_1(":image/image/pauseButton1.png");
        QIcon icon_play_2(":image/image/pauseButton2.png");
        palyButton->setIcons(icon_play_1,icon_play_2);
        palyButton->setToolTip(tr("暂停"));
    }else{
        QIcon icon_play_1(":image/image/playButton1.png");
        QIcon icon_play_2(":image/image/playButton2.png");
        palyButton->setIcons(icon_play_1,icon_play_2);
        palyButton->setToolTip(tr("播放"));
    }
}

void BottomWidget::positionChanged(qint64 value){
    slider->setValue(value);
    if(!totalTime.isEmpty()){
        musicTime->setText(QString("%1/%2").arg(caculateTime(value),totalTime));
    }
}

void BottomWidget::durationChanged(qint64 value){
    slider->setRange(0,value);
    totalTime = caculateTime(value);
}

QString BottomWidget::caculateTime(qint64 value){
    qint64 secs = value / 1000;
    qint64 min = secs / 60;
    qint64 sec = secs % 60;
    QString format;
    format = min < 10 ? "0%1" : "%1";
    format += sec < 10 ? ":0%2" : ":%2";
    return format.arg(min).arg(sec);
}
