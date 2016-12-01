#ifndef BOTTOMWIDGET_H
#define BOTTOMWIDGET_H

#include "movablewidget.h"
#include "mouseslider.h"
#include <QLabel>
#include <QMediaPlayer>
#include "customizebutton.h"

class BottomWidget : public MovableWidget
{
    Q_OBJECT
public:
    explicit BottomWidget(QWidget *parent = 0);
    void setPlayingName(QString songName,QString author=NULL);

signals:
    void previousSong();
    void nextSong();
    void playOrPauseSong();
    void setPostion(int value);

public slots:
    void positionChanged(qint64 value);
    void durationChanged(qint64 value);
    void stateChanged(QMediaPlayer::State state);

private:
    void initPalyButtons(QWidget *parent);
    void initScheduleBar(QWidget *parent);
    QString caculateTime(qint64 value);

    MouseSlider *slider;
    QLabel *musicTime;
    QLabel *musicName1;
    QLabel *musicName2;
    QString totalTime;
    CustomizeButton *palyButton;
};

#endif // BOTTOMWIDGET_H
