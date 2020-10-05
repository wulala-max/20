#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<stdlib.h>
struct pig
{
	double weight;
	int spicy;//1代表黑猪，2代表小白猪，3代表大白猪
	int id2;//猪圈内编号
	int growmonth, growday;//生长时间
	pig * next;//指向下一头猪

};
class Sty2
{

	
	
public:
	pig * head;
	int cntall;
	int isbalck;//是否为黑猪圈,0,1,2
	int id;//猪圈号
	int flag;//是否感染
	int cnt1, cnt2, cnt3;
	Sty2();
	~Sty2();
	void print();
	void addpig(pig * p);
	void insert(int spicy);
	double getprice(int &a, int &b, int &c);
	int getspicy(int i);
	int getgrowmonth(int i);
	int getgrowday(int i);
	double getweight(int i);
	void next(int nexttime);
	bool search(int number);
	void clearsty();
	void setisblack(int i);
	int getspicy1();
	int getspicy2();
	int getspicy3();
	int getcount();
	int isblacksty();
	//void savesty(ofstream &savefile);//写入信息到文件中
	pig * gethead();

};



