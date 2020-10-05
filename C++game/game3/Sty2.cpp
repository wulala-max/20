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

void Sty2::setisblack(int i) {   //����Ϊ�Ƿ�Ϊ�����1��ʾ����Ȧ��0��ʾ�գ�2��ʾ��
	isbalck = i;
}
int Sty2::getspicy1() {//�����Ȧ�ں��������
	int sum = 0;
	for (int i = 0; i < cntall; i++) {
		if (getspicy(i) == 1)
			sum++;
	}
	return sum;
}
int Sty2::getspicy2() {//�����Ȧ��С���������
	int sum = 0;
	for (int i = 0; i < cntall; i++) {
		if (getspicy(i) == 2)
			sum++;
	}
	return sum;
}
int Sty2::getspicy3() {//�����Ȧ�ڴ��������
	int sum = 0;
	for (int i = 0; i < cntall; i++) {
		if (getspicy(i) == 3)
			sum++;
	}
	return sum;
}
int Sty2::getcount() { //���ĳ����Ȧ�������������
	return cntall;

}
int Sty2::isblacksty() {//�ж��Ƿ�Ϊ����Ȧ
	return isbalck;
}
pig * Sty2::gethead() {//�����Ȧ��ͷָ��
	return head;
}
void Sty2::addpig(pig * p) {//����Ȧ�ڲ���һͷ��ָ����ƣ����ܱ�����
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
int Sty2::getspicy(int i) {  //�����Ȧ�ڱ��Ϊi���������
	pig * p = head;
	for (int j = 0; j < i; i++) {
		p = p->next;
	}
	return p->spicy;
}
int Sty2::getgrowmonth(int i) {//�����Ȧ�ڱ��Ϊi���������ʱ��
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
double Sty2::getweight(int i) {//��ȡ����
	pig * p = head;
	for (int j = 0; j < i; i++) {
		p = p->next;
	}
	return p->weight;
}
double Sty2::getprice(int &a,int &b,int &c) {//���һ����Ȧ��ĳ��ʱ���������۸�,������ͷ����������Ȧ����ı��
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
			month++;         //���Ľ�
		}
		if (month >= 12 || p->weight > 75) {//������������

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
				setisblack(0);//��������Ϊ����Ȧ 
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
			head = p;//������ͷ
		}
		p = p1->next;
		p1 = p;
	}
	return sellprice;
}



void Sty2::print() {//��ӡ��Ȧ��Ϣ
	if (cntall == 0) {
		cout << "����Ȧ" << endl;
		return;
	}

	else {

		if (isbalck == 1) {
			cout << "�Ǻ���Ȧ,ȫ���Ǻ���" << endl;
			
		}
		else
			cout << "���Ǻ���Ȧ" << endl;

	}
	pig * p = head;
	cout << "����" << cntall << "ͷ��" << endl;
	while (p) {
		int month = p->growmonth;
		int day = p->growday;
		while (day >= 30) {
			day -= 30;
			month++;
		}
		int  i = p->id2;
		cout << i << "��������" << month << "����" << day << "�죬����Ϊ" << p->weight << "Kg,";
		if (p->spicy == 2) cout << "����ΪС����" << endl;
		if (p->spicy == 3) cout << "����Ϊ����" << endl;
	}
}
void Sty2::next(int nexttime) {//���������Լ�����ʱ��
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
bool Sty2::search(int id2) {//��Ȧ���Ƿ���ڱ��ΪID2����
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
void Sty2::insert(int spicy) {//����Ȧ���²���һͷspicyΪspicy����ֻ��Ҫ�ṩspicy����
	pig * p = new pig;
	srand((unsigned)time(NULL));
	p->spicy = spicy;
	p->weight = rand() % 30 + 20;
	p->growmonth = p->growday = 0;
	if (head == NULL) {//�������Ȧ�����������Ϣ
		p->id2 = 0;
		p->next = NULL;
		head = p;
		cntall++;
		return;
	}
	if (head->id2 != 0) {//�ǿ���Ȧ���ҵ�һͷ�����������head->id2 != 0�����������ͷ��
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
		if (p1->next == NULL) {//��һͷ��δ�������Һ������ID2����������뵽��β
			p->id2 = cntall;
			p->next = NULL;
			p1->next = p;
		}
		else {    //p1->id2 != k���м�������������������ұ��ΪK
			p->id2 = k;
			p2->next = p;
			p->next = p1;
		}
		cntall++;
	}
}
//д����Ϣ���ļ���
