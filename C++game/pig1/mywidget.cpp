#include "mywidget.h"
#include "ui_mywidget.h"
#include"subenter.h"
#include"subhelp.h"
#include<QPalette>
#include<QPushButton>
#include<QPixmap>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    QPixmap pixmap =  QPixmap(":/picture/main.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);
    this->setWindowTitle("养猪游戏");
    QPushButton * bt1=new QPushButton;
    QPushButton *bt2=new QPushButton;
    QPushButton *bt3=new QPushButton;
    bt1->setText("进入游戏");
    bt2->setText("退出游戏");
    bt3->setText("帮助文档");
    bt1->setParent(this);
    bt2->setParent(this);
    bt3->setParent(this);
    this->resize(800,600);
    bt1->move(325,275);
    bt2->move(325,325);
    bt3->move(325,375);
    connect(bt2,&QPushButton::pressed,this,&MyWidget::close);


    connect(bt1,&QPushButton::pressed,this,&MyWidget::myslot1);//进入游戏界面
    connect(bt3,&QPushButton::pressed,this, &MyWidget::myslot3);//打开帮助文档


    connect(&win1,&Subenter::mysignal,this,&MyWidget::dealSub1);//游戏界面退回到主页面
    connect(&win2,&SubHelp::mysignal,this,&MyWidget::dealSub2);//从帮助界面返回到主界面
}
void MyWidget::myslot1(){

    win1.show();
    this->hide();
}
void MyWidget::myslot3(){
    win2.show();
    this->hide();
}
void MyWidget::dealSub1(){
    win1.hide();
    this->show();
}
void MyWidget::dealSub2(){
    win2.hide();
    this->show();
}
MyWidget::~MyWidget()
{
    delete ui;
}


