#ifndef CUSTOMIZEBUTTON_H
#define CUSTOMIZEBUTTON_H

#include <QPushButton>

class CustomizeButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CustomizeButton(QWidget *parent = Q_NULLPTR);
    explicit CustomizeButton(const QString &text, QWidget *parent = Q_NULLPTR);
    ~CustomizeButton();

    void setIcons(QIcon &icon1,QIcon &icon2);

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private:
    QIcon icon1;
    QIcon icon2;
};

#endif // CUSTOMIZEBUTTON_H
