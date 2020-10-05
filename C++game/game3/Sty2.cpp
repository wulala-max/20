#include "Sty2.h"
#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<stdlib.h>
#include<iomanip>
using namespace std;
Sty2::~Sty2()
{
}

Sty2::Sty2()
{
	cntall = 0;
	isbalck = 0;
	head = NULL;
}

void Sty2::setisblack(int i) {   //设置为是否为黑猪卷，1表示黑猪圈，0表示空，2表示白
	isbalck = i;
}
int Sty2::getspicy1() {//获得猪圈内黑猪的数量
	int sum = 0;
	for (int i = 0; i < cntall; i++) {
		if (getspicy(i) == 1)
			sum++;
	}
	return sum;
}
int Sty2::getspicy2() {//获得猪圈内小花猪的数量
	int sum = 0;
	for (int i = 0; i < cntall; i++) {
		if (getspicy(i) == 2)
			sum++;
	}
	return sum;
}
int Sty2::getspicy3() {//获得猪圈内大花猪的数量
	int sum = 0;
	for (int i = 0; i < cntall; i++) {
		if (getspicy(i) == 3)
			sum++;
	}
	return sum;
}
int Sty2::getcount() { //获得某个猪圈的所有猪的数量
	return cntall;

}
int Sty2::isblacksty() {//判断是否为黑猪圈
	return isbalck;
}
pig * Sty2::gethead() {//获得猪圈内头指针
	return head;
}
void Sty2::addpig(pig * p) {//往猪圈内插入一头猪，指针后移，不管标号如何
	cntall++;
	p->next = NULL;
	if (head == NULL) {
		head = p;
	}
	else {
		pig * p1 = head;
		while (p1->next) {
			p1 = p1->next;
		}
		p1->next = p;
	}
}
int Sty2::getspicy(int i) {  //获得猪圈内标号为i的猪的种类
	pig * p = head;
	for (int j = 0; j < i; i++) {
		p = p->next;
	}
	return p->spicy;
}
int Sty2::getgrowmonth(int i) {//获得猪圈内标号为i的猪的生长时间
	pig * p = head;
	for (int j = 0; j < i; i++) {
		p = p->next;
	}
	return p->growmonth;
}
int Sty2::getgrowday(int i) {
	pig * p = head;
	for (int j = 0; j < i; i++) {
		p = p->next;
	}
	return p->growday;
}
double Sty2::getweight(int i) {//获取体重
	pig * p = head;
	for (int j = 0; j < i; i++) {
		p = p->next;
	}
	return p->weight;
}
double Sty2::getprice(int &a,int &b,int &c) {//获得一个猪圈在某个时间点的卖出价格,更新猪头，不更新猪圈内猪的编号
	double sellprice = 0;
	if (head == NULL)
		return 0;
	int month, day, flag = 0;
	pig * p = head, *p1 = p;
	while (p) {
		month = p->growmonth;
		day = p->growday;
		while (day >= 30) {
			day -= 30;
			month++;         //待改进
		}
		if (month >= 12 || p->weight > 75) {//符合卖出条件

			if (p->spicy == 1) {
				sellprice = sellprice+ 30 * p->weight;
				a++;
			}
				
			if (p->spicy == 2) {
				sellprice =sellprice+ 14 * p->weight;
				b++;
			}
				
			if (p->spicy == 3) {
				sellprice =sellprice+ 12 * p->weight;
				c++;
			}
				
			if (cntall == 1) {
				setisblack(0);//卖出后设为空猪圈 
				head = NULL;
				delete p;
				cntall--;
				break;
			}
			p1->next = p->next;

			delete p;
			p = p1->next;
			cntall--;

			continue;
		}
		else if (flag == 0) {
			flag = 1;
			head = p;//更新猪头
		}
		p = p1->next;
		p1 = p;
	}
	return sellprice;
}



void Sty2::print() {//打印猪圈信息
	if (cntall == 0) {
		cout << "空猪圈" << endl;
		return;
	}

	else {

		if (isbalck == 1) {
			cout << "是黑猪圈,全部是黑猪" << endl;
			
		}
		else
			cout << "不是黑猪圈" << endl;

	}
	pig * p = head;
	cout << "共有" << cntall << "头猪" << endl;
	while (p) {
		int month = p->growmonth;
		int day = p->growday;
		while (day >= 30) {
			day -= 30;
			month++;
		}
		int  i = p->id2;
		cout << i << "号猪养了" << month << "个月" << day << "天，体重为" << p->weight << "Kg,";
		if (p->spicy == 2) cout << "种类为小花猪" << endl;
		if (p->spicy == 3) cout << "种类为大花猪" << endl;
	}
}
void Sty2::next(int nexttime) {//更新体重以及饲养时间
	srand((unsigned)time(NULL));
	pig * p = head;
	while (p) {
		p->weight += (double)(rand() % 12)*nexttime / 10;
		if (nexttime == 1)
			p->growday++;
		else
			p->growmonth++;
		p = p->next;
	}
}
bool Sty2::search(int id2) {//猪圈中是否存在标号为ID2的猪
	pig * p = head;
	while (p) {
		if (p->id2 == id2)
			return true;
		else
			p = p->next;

	}
	return false;
}
void Sty2::clearsty() {
	
	if (head == NULL)
		return;

	else {
		pig * p = head;
		pig * p1 = p;
		cntall = 0;
		setisblack(0);
		head = NULL;
		while (p) {
			p1 = p;
			p = p->next;
			delete p1;
		}
		delete p;
	}

}
void Sty2::insert(int spicy) {//往猪圈中新插入一头spicy为spicy的猪，只需要提供spicy即可
	pig * p = new pig;
	srand((unsigned)time(NULL));
	p->spicy = spicy;
	p->weight = rand() % 30 + 20;
	p->growmonth = p->growday = 0;
	if (head == NULL) {//插入空猪圈，配置猪的信息
		p->id2 = 0;
		p->next = NULL;
		head = p;
		cntall++;
		return;
	}
	if (head->id2 != 0) {//非空猪圈，且第一头猪被卖出，因而head->id2 != 0，将新猪插入头部
		p->id2 = 0;
		p->next = head;
		head = p;
		cntall++;
		return;
	}
	else {
		pig * p1 = head, *p2 = p1;
		int k = 0;
		while (p1->id2 == k && p1->next) {
			k++;
			p2 = p1;
			p1 = p1->next;
		}
		if (p1->next == NULL) {//第一头猪未卖出，且后面的猪ID2都有序则插入到队尾
			p->id2 = cntall;
			p->next = NULL;
			p1->next = p;
		}
		else {    //p1->id2 != k，中间有无序猪，则将新猪插入且标号为K
			p->id2 = k;
			p2->next = p;
			p->next = p1;
		}
		cntall++;
	}
}
//写入信息到文件中
