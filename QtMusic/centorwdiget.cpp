#include "centorwdiget.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QScrollArea>
#include "fileoperate.h"
#include <QHeaderView>
#include <QMenu>
#include <QFileDialog>
#include <QDebug>

CentorWdiget::CentorWdiget(QWidget *parent) : QWidget(parent)
{
    QSplitter *splitter = new QSplitter(Qt::Horizontal,this);
    QWidget *leftWidget = new QWidget(splitter);
    QWidget *rightWidget = new QWidget(splitter);
    initLeft(leftWidget);
    initRight(rightWidget);

    splitter->setStretchFactor(0,1);
    splitter->setStretchFactor(1,4);
    splitter->setHandleWidth(1);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    this->setLayout(layout);
    layout->addWidget(splitter);
}

void CentorWdiget::initLeft(QWidget *parent){
    QHBoxLayout *layout = new QHBoxLayout(parent);
    layout->setMargin(0);
    parent->setLayout(layout);

    QScrollArea *scrollArea = new QScrollArea(parent);
    layout->addWidget(scrollArea);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    tree = new QTreeView(scrollArea);
    tree->setAutoFillBackground(true);
//    tree->setPalette(Qt::white);

    layout->addWidget(tree);
    tree->setAutoFillBackground(true);
    QPalette palette = tree->palette();
    palette.setColor(QPalette::Background,Qt::white);
    palette.setColor(QPalette::Text,QColor(68,68,68));
    tree->setPalette(palette);
    QFont font;
    font.setPointSize(11);
    tree->setFont(font);
    tree->setStyleSheet("QTreeWidget::item{height:80px}");

    model = new QStandardItemModel();
    QStandardItem *loveItem = new QStandardItem(menu_mode[0]);
    QStandardItem *historyItem = new QStandardItem(menu_mode[1]);
    QStandardItem *billItem = new QStandardItem(menu_mode[2]);
    QVector<Navigation> navigations;
    FileOperate::readMenuList(navigations);
    QVector<Navigation>::const_iterator iterator;
    QIcon icon(":image/image/musicIcon.png");
    int i=0;
    QStandardItem *currentItem;
    for(iterator=navigations.constBegin();iterator != navigations.constEnd();iterator++,i++){
        QStandardItem *item = new QStandardItem(iterator->name);
        item->setIcon(icon);
        billItem->setChild(i,0,item);
        if(iterator->selected == 1){
            menuName = iterator->name;
            currentItem = item;
        }
    }

    model->setItem(0,0,loveItem);
    model->setItem(1,0,historyItem);
    model->setItem(2,0,billItem);

    tree->setHeaderHidden(true);
    tree->setModel(model);
    tree->expand(billItem->index());
    tree->setEditTriggers(0);
    tree->setCurrentIndex(currentItem->index());
    tree->setContextMenuPolicy(Qt::CustomContextMenu);

    scrollArea->setWidget(tree);
//    connect(tree,SIGNAL(clicked(QModelIndex)),this,SLOT(songMenuSelected(QModelIndex)));
    connect(tree,SIGNAL(pressed(QModelIndex)),this,SLOT(songMenuSelected(QModelIndex)));
    connect(tree,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(songMenuSelectedAndPlay(QModelIndex)));
    connect(tree,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customContextMenuRequested(QPoint)));
}

void CentorWdiget::customContextMenuRequested(const QPoint &pos){
    QModelIndex index = tree->indexAt(pos);
    QString name = index.data().toString();
    QMenu *menu = new QMenu;
    if(name == menu_mode[0]){
        menu->addAction(tr("添加本地音乐"),this,SLOT(addLocalMusic()));
        mode = 0;
    }else if(name == menu_mode[1]){
        mode = 1;
    }else if(name == menu_mode[2]){
        mode = 2;
        menu->addAction(tr("创建歌单"));
    }else{
        mode = 3;
        menu->addAction(tr("播放"));
        menu->addSeparator();
        menu->addAction(tr("删除"));
        menu->addAction(tr("重命名"));
        menu->addSeparator();
        menu->addAction(tr("添加本地音乐"),this,SLOT(addLocalMusic()));
    }
    menu->exec(QCursor::pos());
}

void CentorWdiget::initRight(QWidget *parent){
    QHBoxLayout *layout = new QHBoxLayout(parent);
    layout->setMargin(0);
    parent->setLayout(layout);

    QScrollArea *scrollArea = new QScrollArea(parent);
    layout->addWidget(scrollArea);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    songTable = new QTableView(scrollArea);
    songTable->setAutoFillBackground(true);

    layout->addWidget(songTable);
    songTable->setAutoFillBackground(true);
    QPalette palette = songTable->palette();
    palette.setColor(QPalette::Background,Qt::white);
    palette.setColor(QPalette::Text,QColor(68,68,68));
    songTable->setPalette(palette);
    QFont font;
    font.setPointSize(11);
    songTable->setFont(font);
    songTable->setStyleSheet("QTreeWidget::item{height:80px}");

    songModel = new QStandardItemModel();

    songModel->setHorizontalHeaderItem(0,new QStandardItem(tr("歌曲")));
    songModel->setHorizontalHeaderItem(1,new QStandardItem(tr("歌手")));

    songTable->setShowGrid(false);
    songTable->setSelectionBehavior(QTableView::SelectRows);
    songTable->setSelectionMode(QTableView::SingleSelection);
    songTable->setEditTriggers(0);
    songTable->setModel(songModel);
    songTable->verticalHeader()->hide();
    songTable->horizontalHeader()->setStretchLastSection(true);
    songTable->setColumnWidth(0,400);
    songTable->setColumnHidden(2,true);
    scrollArea->setWidget(songTable);

    connect(songTable,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(songSelected(QModelIndex)));
}

void CentorWdiget::initMenu(){
    updateSongMenu(menuName);
    updatePlayingMenu();
}

void CentorWdiget::addLocalMusic(){
    QString filter("mp3(*.mp3);;All(*.*)");
    QList<QUrl> list = QFileDialog::getOpenFileUrls(this,tr("导入本地文件"),QString(getenv("HOME")),filter);
    for(int i=0;i < list.size();i++){
        QUrl url = list.at(i);
        if(!checkSongExit(url)){
            continue;
        }
        QString filename = url.fileName();
        QList<QStandardItem*> list;
        if(filename.contains(" - ")){
            QStringList names = filename.split(" - ");
            QStandardItem *item = new QStandardItem(names.at(1));
            item->setData(url);
//            songModel->setItem(i,0,item);
            list.append(item);
            item = new QStandardItem(names.at(0));
//            songModel->setItem(i,1,item);
            list.append(item);
        }else{
            QStandardItem *item = new QStandardItem(filename);
            item->setData(url);
//            songModel->setItem(i,0,item);
            list.append(item);
        }
        songModel->insertRow(i,list);
        emit addSong(url,i);
    }

    QVector<Song> songs;
    for(int i=0;i < songModel->rowCount();i++){
        Song song;
        song.name = songModel->item(i,0)->text();
        song.url = songModel->index(i,0).data(Qt::UserRole + 1).toUrl().toString();
        song.author = songModel->item(i,1)->text();
        songs.append(song);
    }
    FileOperate::updateMenu(menuName,songs);
}

void CentorWdiget::updateSongMenu(QString name){
    if(name.isEmpty()){
        return;
    }
    QVector<Song> songs;
    FileOperate::readMenu(name,songs);
    QVector<Song>::const_iterator iterator;
    songModel->removeRows(0,songModel->rowCount());
    int i=0;
    for(iterator = songs.constBegin();iterator != songs.constEnd();iterator++,i++){
        if(!iterator->name.isEmpty()){
            QStandardItem *item = new QStandardItem(iterator->name);
            if(!iterator->url.isEmpty()){
                QUrl url(iterator->url);
                item->setData(url);
            }
            songModel->setItem(i,0,item);
        }
        if(!iterator->author.isEmpty()){
            QStandardItem *item = new QStandardItem(iterator->author);
            songModel->setItem(i,1,item);
        }
    }
    menuName = name;
    emit playingMenu();
}

void CentorWdiget::songMenuSelected(QModelIndex index){
    QString name = index.data().toString();
    updateSongMenu(name);
}
void CentorWdiget::songMenuSelectedAndPlay(QModelIndex index){
    QString name = index.data().toString();
    if(name != menuName){
        updateSongMenu(name);
    }
    updatePlayingMenu();
    emit playMusic(0);
}

void CentorWdiget::songSelected(QModelIndex index){
    updatePlayingMenu();
    emit playMusic(index.row());
}
void CentorWdiget::updatePlayingMenu(){
    int rows = songModel->rowCount();
    QVector<QUrl> songs;
    for(int i=0;i < rows;i++){
        songs.append(songModel->index(i,0).data(Qt::UserRole + 1).toUrl());
    }
    FileOperate::updateMenuSelected(menuName);
    emit changPlayMenu(menuName,songs);
}

void CentorWdiget::songName(QString menu,int index, QString *name){
    if(menu != menuName || index == -1){
        return;
    }
    if(index < songModel->rowCount()){
        if(name){
            *name = songModel->item(index,0)->text();
            *(name+1) = songModel->item(index,1)->text();
        }
        songModel->item(index,0)->setForeground(QBrush(QColor(45,195,124)));
        songModel->item(index,1)->setForeground(QBrush(QColor(45,195,124)));
    }
    for(int i=0;i < songModel->rowCount();i++){
        if(i != index){
            songModel->item(i,0)->setForeground(QBrush(Qt::black));
            songModel->item(i,1)->setForeground(QBrush(Qt::black));
        }
    }
}

void CentorWdiget::changeMenu(QString menu){
    for(int i=0;i < model->rowCount();i++){
        QString _menu = model->item(i,0)->text();
        if(_menu == menu){
            model->item(i,0)->setForeground(QBrush(QColor(45,195,124)));
        }else{
            model->item(i,0)->setForeground(QBrush(Qt::black));
            changeMenu(model->item(i,0),menu);
        }
    }
}

void CentorWdiget::changeMenu(QStandardItem *item,QString menu){
    if(item->hasChildren()){
        for(int i=0;i < item->rowCount();i++){
            QString _menu = item->child(i,0)->text();
            if(_menu == menu){
                item->child(i,0)->setForeground(QBrush(QColor(45,195,124)));
            }else{
                item->child(i,0)->setForeground(QBrush(Qt::black));
                changeMenu(item->child(i,0),menu);
            }
        }
    }
}

bool CentorWdiget::checkSongExit(QUrl &url){
    for(int i=0;i < songModel->rowCount();i++){
        QUrl _url = songModel->index(i,0).data(Qt::UserRole + 1).toUrl();
        if(_url == url){
            return false;
        }
    }
    return true;
}
