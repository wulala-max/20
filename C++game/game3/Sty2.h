#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<stdlib.h>
struct pig
{
	double weight;
	int spicy;//1�������2����С����3��������
	int id2;//��Ȧ�ڱ��
	int growmonth, growday;//����ʱ��
	pig * next;//ָ����һͷ��

};
class Sty2
{

	
	
public:
	pig * head;
	int cntall;
	int isbalck;//�Ƿ�Ϊ����Ȧ,0,1,2
	int id;//��Ȧ��
	int flag;//�Ƿ��Ⱦ
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
	//void savesty(ofstream &savefile);//д����Ϣ���ļ���
	pig * gethead();

};



