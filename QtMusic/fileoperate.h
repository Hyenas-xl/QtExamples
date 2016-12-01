#ifndef FILEOPERATE_H
#define FILEOPERATE_H

#include <QObject>
class QDomElement;

struct Song{
    QString name;
    QString author;
    QString url;
};
struct Navigation{
    QString name;
    int selected;
};

class FileOperate
{
public:
    /**
     * @brief readMenu  读取歌单内容
     * @param name      歌单名
     * @param songs     歌单内容
     */
    static void readMenu(QString name,QVector<Song> &songs);
    /**
     * @brief readMenuList 获取所有歌单集合
     * @param navigations  歌单集合
     */
    static void readMenuList(QVector<Navigation> &navigations);
    /**
     * @brief updateMenuSelected  更新默认选择歌单
     * @param name                默认歌单
     */
    static void updateMenuSelected(QString name);
    /**
     * @brief updateMenu    更新歌单内容
     * @param name          歌单
     * @param songs         歌单内容
     */
    static void updateMenu(QString name,QVector<Song> &songs);
signals:

public slots:

private:
    static QDomElement createSongElement(QDomElement child,Song &song);
    static void createSongMenuFile(QString name,QVector<Song> &songs);
};

#endif // FILEOPERATE_H
