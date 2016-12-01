#ifndef CENTORWDIGET_H
#define CENTORWDIGET_H

#include <QUrl>
#include <QWidget>
#include <QTreeView>
#include <QTableView>
#include <QStandardItemModel>
#include <QJsonDocument>

class CentorWdiget : public QWidget
{
    Q_OBJECT
public:
    explicit CentorWdiget(QWidget *parent = 0);
    void songName(QString menu,int index,QString *name = 0);
    void initMenu();
    void changeMenu(QString menu);

signals:
    void addSong(QUrl song,int pos);
    void changPlayMenu(QString name,QVector<QUrl> &songs);
    void playMusic(int index);
    void playingMenu();

public slots:
    void songMenuSelected(QModelIndex index);
    void songMenuSelectedAndPlay(QModelIndex index);
    void songSelected(QModelIndex index);
    void customContextMenuRequested(const QPoint &pos);
    void addLocalMusic();

private:
    void initLeft(QWidget *parent);
    void initRight(QWidget *parent);
    void updateSongMenu(QString name);
    void updatePlayingMenu();
    bool checkSongExit(QUrl &url);
    void changeMenu(QStandardItem *item,QString menu);

    const QString menu_mode[3] = {tr("我喜欢"),tr("播放历史"),tr("我的歌单")};
    int mode = -1;
    QTreeView *tree;
    QStandardItemModel *model;
    QJsonDocument json;
    QTableView *songTable;
    QStandardItemModel *songModel;
    QJsonDocument songjson;
    QString menuName;
};

#endif // CENTORWDIGET_H
