#include "customizebutton.h"
#include <QEvent>
#include "imagetool.h"

CustomizeButton::CustomizeButton(const QString &text, QWidget *parent):QPushButton(text,parent){

    this->setStyleSheet("QPushButton:hover{color:red}");
}
CustomizeButton::CustomizeButton(QWidget *parent):QPushButton(parent){

}
CustomizeButton::~CustomizeButton(){
//    delete this->icon1;
//    delete this->icon2;
}

void CustomizeButton::setIcons(QIcon &icon1, QIcon &icon2){
    this->icon1 = icon1;
    this->icon2 = icon2;
    this->setIcon(icon1);
}

void CustomizeButton::enterEvent(QEvent *event){
    Q_UNUSED(event);
    this->setIcon(this->icon2);
}
void CustomizeButton::leaveEvent(QEvent *event){
    Q_UNUSED(event);
    this->setIcon(this->icon1);
}
