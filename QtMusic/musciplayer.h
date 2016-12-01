#ifndef MUSCIPLAYER_H
#define MUSCIPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class MusciPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MusciPlayer(QObject *parent = 0);

    void setVolume(int value);
    int volume() const;
    int currentIndex() const;
    QString menuName() const;
    QMediaPlaylist::PlaybackMode palyBackMode();

signals:
    void positionChanged(qint64 value);
    void durationChanged(qint64 value);
    void stateChanged(QMediaPlayer::State newState);
    void currentIndexChanged(int index);

public slots:
    void playMusic();
    void playMusicByIndex(int index);
    void setPostion(int value);
    void changeMenu(QString name,QVector<QUrl> &urls);
    void addSong(QUrl url,int pos = 0);
    void cleanMenu();
    void nextSong();
    void previousSong();
    void setPlaybackMode(QMediaPlaylist::PlaybackMode mode);
    void setMuted(bool muted);
    bool isMuted();

private:
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QString _menuName;
    int _volumeNum = 80;
};

#endif // MUSCIPLAYER_H
