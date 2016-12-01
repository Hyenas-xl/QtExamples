#include "musciplayer.h"
#include <QDebug>

MusciPlayer::MusciPlayer(QObject *parent) : QObject(parent)
{
    player = new QMediaPlayer;
    playlist = new QMediaPlaylist;
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(playlist);
    setVolume(_volumeNum);

    connect(player, SIGNAL(positionChanged(qint64)), this, SIGNAL(positionChanged(qint64)));
    connect(player,SIGNAL(durationChanged(qint64)),this,SIGNAL(durationChanged(qint64)));
    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SIGNAL(stateChanged(QMediaPlayer::State)));
    connect(playlist,SIGNAL(currentIndexChanged(int)),this,SIGNAL(currentIndexChanged(int)));

}

int MusciPlayer::currentIndex() const{
    return playlist->currentIndex();
}

void MusciPlayer::setVolume(int value){
    if(player){
        player->setVolume(value);
    }
}

int MusciPlayer::volume() const{
    if(player){
        return player->volume();
    }
    return 0;
}

void MusciPlayer::addSong(QUrl url,int pos){
    playlist->insertMedia(pos,url);
}
void MusciPlayer::changeMenu(QString name,QVector<QUrl> &urls){
    if(!name.isEmpty() && name != _menuName){
        playlist->clear();
        this->_menuName = name;
        QVector<QUrl>::const_iterator iterator;
        for(iterator = urls.constBegin();iterator != urls.constEnd();iterator++){\
            playlist->addMedia(*iterator);
        }
    }
}
void MusciPlayer::cleanMenu(){
    playlist->clear();
}

void MusciPlayer::playMusicByIndex(int index){
    playlist->setCurrentIndex(index);
    player->play();
}

void MusciPlayer::playMusic(){
    if(player->state() == QMediaPlayer::PlayingState){
        player->pause();
    }else{
        player->play();
    }
}

void MusciPlayer::setPostion(int value){
    player->setPosition(value);
}
void MusciPlayer::setMuted(bool muted){
    player->setMuted(muted);
}
bool MusciPlayer::isMuted(){
    return player->isMuted();
}

QString MusciPlayer::menuName() const{
    return _menuName;
}

void MusciPlayer::nextSong(){
    playlist->next();
}

void MusciPlayer::previousSong(){
    playlist->previous();
}

void MusciPlayer::setPlaybackMode(QMediaPlaylist::PlaybackMode mode){
    playlist->setPlaybackMode(mode);
}

QMediaPlaylist::PlaybackMode MusciPlayer::palyBackMode(){
    return playlist->playbackMode();
}
