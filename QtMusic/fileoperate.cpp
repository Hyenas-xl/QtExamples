#include "fileoperate.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QDebug>

void FileOperate::readMenu(QString name,QVector<Song> &songs){
    QFile file(QString("%1/QtMusic/conf/menu.xml").arg(getenv("APPDATA")));
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        return;
    }
    QXmlStreamReader reader(&file);
    bool selectMenu = false;
    while (!reader.atEnd() && !reader.hasError()) {
        reader.readNext();
        if(reader.isStartElement()){
            if(reader.name() == "menu"){
                QXmlStreamAttributes attributes = reader.attributes();
                if(attributes.hasAttribute("name") && attributes.value("name").toString() == name){
                    selectMenu = true;
                }
            }else if(reader.name() == "item" && selectMenu){
                QXmlStreamAttributes attributes = reader.attributes();
                Song song;
                if(attributes.hasAttribute("name")){
                    song.name = attributes.value("name").toString();
                }
                if(attributes.hasAttribute("author")){
                    song.author = attributes.value("author").toString();
                }
                if(attributes.hasAttribute("url")){
                    song.url = attributes.value("url").toString();
                }
                songs.append(song);
            }
        }else if(reader.isEndElement()){
            if(reader.name() == "menu"){
                selectMenu = false;
            }
        }
    }
    file.close();
}

void FileOperate::readMenuList(QVector<Navigation> &navigations){
    QFile file(QString("%1/QtMusic/conf/navigation.xml").arg(getenv("APPDATA")));
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        return;
    }
    QXmlStreamReader reader(&file);
    bool selectMenu = false;
    while (!reader.atEnd() && !reader.hasError()) {
        reader.readNext();
        if(reader.isStartElement()){
            if(reader.name() == "menu"){
                QXmlStreamAttributes attributes = reader.attributes();
                if(attributes.hasAttribute("name") && attributes.value("name").toString() == "songMenu"){
                    selectMenu = true;
                }
            }else if(reader.name() == "item" && selectMenu){
                QXmlStreamAttributes attributes = reader.attributes();
                Navigation navigation;
                if(attributes.hasAttribute("name")){
                    navigation.name = attributes.value("name").toString();
                }
                if(attributes.hasAttribute("selected")){
                    navigation.selected = attributes.value("selected").toInt();
                }
                navigations.append(navigation);
            }
        }else if(reader.isEndElement()){
            if(reader.name() == "menu"){
                selectMenu = false;
            }
        }
    }
    file.close();
}

void FileOperate::updateMenuSelected(QString name){
    QFile file(QString("%1/QtMusic/conf/navigation.xml").arg(getenv("APPDATA")));
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        return;
    }
    QDomDocument doc;
    if(!doc.setContent(&file)){
        file.close();
        return;
    }
//    file.close();
    QDomNodeList nodeList = doc.elementsByTagName("item");
    if(nodeList.count() > 0){
        bool updated = false;
        for(int i=0;i < nodeList.count();i++){
            QDomNode node = nodeList.at(i);
            if(node.isElement()){
                QDomElement  _e = node.toElement();
                if(_e.attribute("name") == name && _e.attribute("selected") != "1"){
                    _e.setAttribute("selected","1");
                    updated = true;
                }else if(_e.attribute("name") != name && _e.attribute("selected") == "1"){
                    _e.setAttribute("selected","0");
                    updated = true;
                }
            }
        }
        file.close();
        if(updated){
            if(!file.open(QFile::WriteOnly | QFile::Text)){
                return;
            }
            QTextStream stream(&file);
            doc.save(stream,4);
            file.close();
        }
    }
}

void FileOperate::updateMenu(QString name, QVector<Song> &songs){
    QFile file(QString("%1/QtMusic/conf/menu.xml").arg(getenv("APPDATA")));
    if(!file.exists()){
        createSongMenuFile(name,songs);
        return;
    }
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        return;
    }
    QDomDocument doc;
    if(!doc.setContent(&file)){
        file.close();
        return;
    }
    file.close();

    QDomNodeList nodeList = doc.elementsByTagName("menu");
    if(nodeList.count() > 0){
        bool updated =false;
        for(int i=0;i < nodeList.count();i++){
            QDomNode node = nodeList.at(i);
            if(node.isElement()){
                QDomElement  _e = node.toElement();
                if(_e.attribute("name") == name){
                    updated = true;
                    QDomNodeList children = _e.childNodes();
                    if(children.count() > 0){
                        int count = children.count();
                        for(int j=0;j < count;j++){
                            _e.removeChild(children.at(0));
                        }
                    }
                    for(int j=0;j < songs.size();j++){
                        Song song = songs.at(j);
                        QDomElement _child = doc.createElement("item");
                        _e.appendChild(createSongElement(_child,song));
                    }
                }
            }
        }
        if(!updated){
            QDomNodeList nodeList = doc.elementsByTagName("menus");
            if(nodeList.count() == 1){
                QDomElement child = doc.createElement("menu");
                child.setAttribute("name",name);
                nodeList.at(0).appendChild(child);
                for(int j=0;j < songs.size();j++){
                    QDomElement _child = doc.createElement("item");
                    Song song = songs.at(j);
                    child.appendChild(createSongElement(_child,song));
                }
            }
        }

        if(!file.open(QFile::WriteOnly | QFile::Text)){
            return;
        }
        QTextStream stream(&file);
        doc.save(stream,4);
        file.close();
    }
}

void FileOperate::createSongMenuFile(QString name, QVector<Song> &songs){
    QFile file(QString("%1/QtMusic/conf/menu.xml").arg(getenv("APPDATA")));
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        return;
    }
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.setAutoFormattingIndent(4);
    writer.writeStartDocument();
    writer.writeStartElement("menus");
    writer.writeStartElement("menu");
    writer.writeAttribute("name",name);
    for(int i=0;i < songs.size();i++){
        writer.writeStartElement("item");
        writer.writeAttribute("name",songs.at(i).name);
        writer.writeAttribute("author",songs.at(i).author);
        writer.writeAttribute("url",songs.at(i).url);
        writer.writeEndElement();
    }
    writer.writeEndElement();
    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();
}

QDomElement FileOperate::createSongElement(QDomElement child,Song &song){
    child.setAttribute("name",song.name);
    child.setAttribute("author",song.author);
    child.setAttribute("url",song.url);
    return child;
}
