#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include"subenter.h"
#include"subhelp.h"

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();
    void myslot1();
    void myslot3();
    void dealSub1();//处理游戏界面窗口发来的信号
    void dealSub2();

private slots:


private:
    Ui::MyWidget *ui;
   Subenter  win1;
   SubHelp  win2;
   // SubHelp
  //  Sty s[100];
};

#endif // MYWIDGET_H
