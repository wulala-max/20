#include "Sty2.h"
#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<stdlib.h>
#include<iomanip>
using namespace std;
double money;
int month, day;//������һ�γ�Ȧʱ��
int allpig;
int sellcnt;//��Ȧ��������ʼ��ӦΪ0

int dead1, dead2, dead3, deadall;//��������ʱ���������������
int getallpig(Sty2 s[]) {//��������������������
	int allcount = 0;
	for (int i = 0; i < 100; i++) {
		allcount += s[i].getcount();
	}
	return allcount;
}

void savesty(Sty2 s,ofstream &savefile) {//��ĳһ��Ȧ�����������Ϣ�����ļ���
	if (s.head == NULL) {
		savefile << '$' << endl;//getspicy(i)Ϊ'$'����ǰ��ȦΪ����Ȧ
		return;
	}
	else {
		pig * p =s.head;

		savefile << s.cntall << endl;
		while (p) {
			savefile << p->id2<< s.getspicy(p->id2) << s.getweight(p->id2) << s.getgrowmonth(p->id2)  << s.getgrowday(p->id2) << endl;//�����⣬���Ǳ�ŶԲ���

			p = p->next;
		}
	}
}
void Menustybyfile(Sty2 s[]) {
	ifstream getinfo;
	getinfo.open("comprehensive.txt");
	getinfo >> allpig >> money >> month >> day >> sellcnt;//д���ļ����ܵ������������������ʱ�䣬����Ȧ����
	getinfo.close();
	ifstream read;
	read.open("stys.txt");//123.txt
	if (!read) {
		cout << "��ȡ���������ʧ��";
		exit(0);
	}
	int t, cntnum;
	pig * p;  //���ļ���ȡ������ÿͷ�����Ϣ��'$'�������Ȧ
	read >> t;//t��־λ
	for (int i = 0; i < 100; i++) {
		read >> cntnum;
		for (int j = 0; j < cntnum; j++) {
			p = new pig;
			//p->id2 = j;
			read >> p->id2;
			read >> p->spicy;
			if (p->spicy == '$') {//��ʾ����ȦΪ�գ�ɨ����һ����Ȧ
				delete p;
				break;
			}
			else
				read >> p->weight >> p->growmonth >> p->growday;
			s[i].addpig(p);
		}
	}
	read.close();
}
//����
void buypig(int bpig, int lpig, int wpig, Sty2 s[]) {//ǰ����������Ϊ��������������������������Ľ�
	while (bpig--) {//���������������ǿ���ȫ����������
		for (int i = 0; i < 100; i++) {
			if (s[i].isblacksty() == 1 && s[i].getcount() < 10) {
				s[i].insert(1);
				break;
			}
			if (s[i].gethead() == NULL) {
				s[i].insert(1);
				s[i].setisblack(1);
				break;
			}
		}
	}
	int aver = allpig / 100 + 1;
	while (1) {
		for (int i = 0; i < 100; i++) {
			if (s[i].isblacksty() == 0) {
				if (lpig > 0 && s[i].getcount() <= aver) {//��֤ƽ�����룬�����Ƚϴֲڣ����Ľ�
					s[i].insert(2);
					lpig--;
				}
				if (wpig > 0 && s[i].getcount() <= aver) {
					s[i].insert(3);
					wpig--;
				}
			}
		}
		if (lpig == 0 && wpig == 0)
			break;
	}
}



void savecomprehensive() {
	ofstream save;
	save.open("comprehensive.txt");//��������Ϣ����������������������ʱ��
	if (!save) {
		cout << "�޷��򿪣�����ȫ�ֱ���ʧ��" << endl;
	}
	else {
		
		save <<allpig  << money << month << day    << sellcnt<<endl;
		cout << "����ɹ�" << endl;
		save.close();
	}

}

/*��1���������ѯ��ǰĳһ��Ȧ��������������ࣻ
��2���������ѯ��ǰĳһ��Ȧĳͷ���״̬��Ϣ��
��3��������ͳ�Ƶ�ǰ��ÿ��Ʒ��������������ء�����ʱ��ֲ������������70������
��4���������ѯ��5��������ۼ�¼�����̶��Ĺ����¼����¼���ļ���ʽ�洢����*/
void sbsty(int sellpignum, double sellprice, int bpig, int lpig, int wpig) {//��¼��Ȧ��Ϣ,��������ĸ������������
	ifstream testin;
	testin.open("sbsty.txt");
	char flag;
	testin >> flag;
	if (flag == '#') {
		testin.close();
		ofstream testout;
		testout.open("sbsty.txt");//�г�Ȧ��¼���һ���ַ���Ϊ$,Ȼ����ԭ�м�¼�����
		testout << '$';
		testout.close();
	}
	else {
		testin.close();
	}
	ofstream save("sbsty.txt", ios::app);//������ʽ��ÿ��д������ݶ��ӵ�β��
	//���������������۸�����۸����������������
	save << sellcnt;//��Ȧ����
	save << sellpignum << "  " << sellprice << "  " << bpig << "  " << lpig << "  " << wpig << "  " << 2000 * bpig + 1500 * lpig + 300 * wpig << endl;;
	save.close();
}
void readsbsty() {
	ifstream read;
	read.open("sbsty.txt");//��Ȧ��Ϣ�ļ�
	if (!read) {
		cout << "�򿪳�Ȧ��Ϣ�ļ�ʧ��";
		exit(0);
	}
	char flag;
	read >> flag;
	if (flag == '#') {
		cout << "�޼�¼" << endl;
		return;
	}
	int times, outpigs, sellprice, bpig, lpig, wpig, cost;//memlast;// memlast��ɶ����
	while (!read.eof()) {
		read >> times;//��Ӧsellcnt
		/* (memlast == times) {
			flag = 1;
			continue;
		}*/
		//memlast = times;
		read >> outpigs >> sellprice >> bpig >> lpig >> wpig >> cost;
		cout << "��" << (times+3) / 4 + 1 << "��";
		cout << "��" << ((times +9)% 12 + 1) << "����" << endl;//���ʱ��
		cout << "��Ȧ������: " << outpigs << "   ������棺 " << sellprice << "  ����������� " << bpig << "  ����С�������� " << lpig << "  ��������� " << wpig << " ������ " << cost << endl;
	}
}

void savefile(Sty2 s[]) {
	ofstream savefile;
	savefile.open("stys.txt");//������������ÿֻ�����Ϣ
	if (!savefile) {
		cout << "�򿪱����ļ�ʧ��";
		exit(0);
	}
	savefile << 1 << endl;//��ʼ��Ϊ0���������ݺ����Ϊ1
	for (int i = 0; i < 100; i++) {//����Ϣ�����ļ���
	    savesty(s[i],savefile);
	}
	savefile.close();
}
void deadday(Sty2 s[],int id) {/*����ĳһֻ�������������������չ�����ǣ�ͬһ����Ȧ����ÿ�챻��Ⱦ������50%��
					   ������Ȧ����ÿ�챻��Ⱦ�ļ�����15%�������ڵ���Ȧ������Ⱦ����д����ģ���ú�������������⡣*/
					   //�������еĸ�Ⱦ�������ݹ�������
	s[id].flag = true;
	int deadall = 0; int day;
	int sum = allpig;
	for (day = 1; deadall < sum; day++) {
		for (int i = 0; i < 99; i++) {//ÿ�����ÿ����Ȧ������
			if (s[i].flag == 2) {
				//0��ʾδ��Ⱦ��1��ʾ������Ⱦ��2��ʾ��Ⱦ��
				//�ȸ���ÿ��ÿ����Ȧ�ĸ�Ⱦ�������������һ���������
				if (i == 0 && s[1].flag == 0) {
					s[1].flag = 1;

				}
				else if (i == 99 && s[99].flag == 0) {
					s[98].flag = 1;
				}
				else {
					if (s[i - 1].flag == 0)
						s[i - 1].flag = 1;
					if (s[i + 1].flag == 0)
						s[i + 1].flag = 1;
				}
			}
			else
				continue;

		}
		for (int i = 0; i < 99; i++) {
			if (s[i].flag == 2)
				deadall = int(s[i].getcount() / 2 + 0.5);
			else if (s[i].flag == 1)
				deadall = int(s[i].getcount()*0.15 + 0.5);
			else
				continue;
		}
	}

	cout << "������ȡ��ʩ��" << day << "��������������������" << endl;
}
void chuli(Sty2 s[], int id) {
	int t1 = 0;
	int t2 = 0;
	if (s[id].cnt1 != 0) {//����Ȧ
		int temp = int(s[id].cnt1*0.15 + 0.5);
		dead1 += temp;//�����������ȡ�� ,����������ȡ
		s[id].cntall = s[id].cnt1 = int(s[id].cnt1 *0.85);
		pig * p = s[id].head,*p1 =p;
		for (int i = 0; i < temp; i++) {
			
				p1 = p;
				p = p->next;
				delete p1;
			
		}
	}
	else
	{    //���Ǵ���������Ȧ�ĺ�������ô������Ȧ����һ���������н��
		//�������ϣ���Ĭ��ʣ����������������ȡ����Ȼ���ȼ���С����ʣ������������ռ�ȼ��㣬ʣ���������ٷ���������
		//ֱ��ȡ��������Ȼ��ȥ������ָ��˳��
		//deadall = int(s[id].cntall*0.15 + 0.5);
		int temp = int(s[id].cnt1*0.15 + 0.5);
		/*t1 = int(double(s[id].cnt1*deadall) / s[id].cntall + 0.5);//С��������������
		t2 = deadall - t1;//�������������
		dead2 += t1;
		dead3 += t2;
		s[id].cntall = s[id].cntall - deadall;
		s[id].cnt1 = s[id].cnt1 - t1;
		s[id].cnt2 = s[id].cnt2 - t2;*/
		pig * p = s[id].head, *p1 = p;
		for (int i = 0; i < temp; i++) {

			p1 = p;
			if (p1->spicy == 2)
				dead2++;
			else
				dead3++;
			p = p->next;
			delete p1;

		}
		s[id].cnt2 -= dead2;
		s[id].cnt3 -= dead3;
		s[id].cntall = s[id].cntall - dead2 - dead3;
	}
}
void Menu_initgame() {//��ʼ��Ϸ������Ӳ˵�
	system("cls");//���
	cout << "\n\n\n\n\n\n";
	cout << "            ==============================================================================\n";
	cout << "                         �ҵ���                                                        \n";
	cout << "                           1.��ѯ\n";
	cout << "                           2.��Ȧ������\n";
	cout << "                           3.������Ϸ\n";
	cout << "                           4.������Ϸ\n";
	cout << "                           8.���س�ʼ����\n";

	cout << "        5.��һ��                   6.�¸���\n";
	cout << "                  7.��������                          \n";
	cout << endl;
	cout << "        ��ǰ�������" << money << "  ��������" << allpig << "�����ϴγ�Ȧʱ�䣺";

	if (month > 0)cout << month << "����";
	if (day >= 0)cout << day << "��";
	cout << endl;
	cout << "            ==============================================================================\n";
}
void dealdisease(Sty2 s[], int id) {//�����ߵ���ɱ����δ�õļ������������������Լ���Ȧ�����Ϣ
	dead1 = dead2 = dead3 = deadall = 0;//���Ӧ�ÿ�������������ڣ�����Ȧ��һ�������ٵ���
	int t1 = 0;
	int t2 = 0;
	if (s[id].getcount() != 0) {//����Ȧ
		dead1 = (s[id].cntall + 1) / 2;//�����������ȡ�� ,����������ȡ
		s[id].cntall = s[id].cnt1 = s[id].cnt1 / 2;
	}

	else {
		deadall = int(s[id].cntall*0.5 + 0.5);
		t1 = int(double(s[id].cnt1*deadall) / s[id].cntall + 0.5);//С��������������
		t2 = deadall - t1;
		dead2 += t1;
		dead3 += t2;
		s[id].cntall = s[id].cntall - deadall;
		s[id].cnt1 = s[id].cnt1 - t1;
		s[id].cnt2 = s[id].cnt2 - t2;
	}

	if (id == 0)
	{
		chuli(s, 1);
	}
	else if (id == 99) {
		chuli(s, 98);
	}
	else {
		chuli(s, id - 1);
		chuli(s, id + 1);
	}
	deadall = dead1 + dead2 + dead3;
	allpig -= deadall;
	cout << "�˴������к�������" << dead1 << "ֻ��С��������" << dead2 << "ֻ����������" << dead3 << "ֻ" << endl;
	cin.get();
	cin.get();
	Menu_initgame();
}

// cnt1,cnt2,cnt3����ʾ��ǰ��ÿ�����������������ʱ������������һ����һ���ں�һ�����ϣ����ط�75kg���µ�
void printdetail(Sty2 s[]) {//��ѯÿ��������أ�����ʱ��ֲ����
	int bw0, bw1, bt0, bt1, lw0, lw1, lt0, lt1, ww0, ww1, wt0, wt1;
	int cnt1=0, cnt2=0, cnt3=0;//�����������
	bw0=bw1=bt0=bt1=lw0= lw1=lt0= lt1=ww0=ww1= wt0=wt1=0;//�ڣ�С����
	for (int i = 0; i < 100; i++) {
		pig * p = s[i].head;
		if (p == NULL)
			continue;
		while (p) {
			if (p->spicy == 1) {
				if (p->growmonth > 12)
					bt1++;
				else
					bt0++;
				if (p->weight > 75)
					bw1++;
				else
					bw0++;
				cnt1++;
			}
			if (p->spicy == 2) {
				if (p->growmonth > 12)
					lt1++;
				else
					lt0++;
				if (p->weight > 75)
					lw1++;
				else
					lw0++;
				cnt2++;
			}
			if (p->spicy == 3) {
				if (p->growmonth > 12)
					wt1++;
				else
					wt0++;
				if (p->weight > 75)
					ww1++;
				else
					ww0++;
				cnt3++;
			}
		}
	}
	double r1 = double(bw1) / cnt1, r2 = 1 - r1, r3 = double(bt1) / cnt1, r4 = 1 - r3;
	double r5 = double(lw1) / cnt2, r6 = 1 - r5, r7 = double(lt1) / cnt2, r8 = 1 - r7;
	double r9 = double(ww1) / cnt3, r10 = 1 - r9, r11 = double(wt1) / cnt3, r12 = 1 - r11;
	cout << "������������75��������ռ��Ϊ" << r1 << "%" << ",75����ռ��Ϊ" << r2 << ";����ʱ����һ�����ϵ�ռ��Ϊ" << r3 << "��һ������ռ��Ϊ" << r4 << endl;
	cout << "С������������75��������ռ��Ϊ" << r5 << "%" << ",75����ռ��Ϊ" << r6 << ";����ʱ����һ�����ϵ�ռ��Ϊ" << r7 << "��һ������ռ��Ϊ" << r8 << endl;
	cout << "������������75��������ռ��Ϊ" << r9 << "%" << ",75����ռ��Ϊ" << r10 << ";����ʱ����һ�����ϵ�ռ��Ϊ" << r11 << "��һ������ռ��Ϊ" << r12 << endl;
}


void Menustys(Sty2 s[]) {//��ʼ����Ϸ������ȷ����ʼ������������࣬�����Լ���Ȧ����ͽ����
	allpig = 500;
	money = 20000;
	month = 0;
	day = 0;
	sellcnt = 0;
	ofstream f;
	f.open("stys.txt");  //123.txt
	f << 1;//��ʾ������Ϊ0����ʼ״̬����
	f.close();
	f.open("sbsty.txt");  //456.txt
	f << '#';//��Ȧ��¼Ϊ��
	f.close();
	pig * p;
	int number = 500;
	srand((unsigned)time(NULL));

	while (number) {//Ϊÿͷ�������Ȧ

		p = new pig;
		p->spicy = rand() % 3 + 1;
		p->weight = rand() % 30 + 20;
		p->growmonth = 0;
		p->growday = 0;
		for (int i = 0; i < 100; i++) {
			if (p->spicy == 1 && (s[i].isblacksty() == 1 || s[i].gethead() == NULL) && s[i].getcount() < 10) {
				p->id2 = s[i].getcount();
				s[i].addpig(p);
				s[i].setisblack(1);//����ʼΪ��������Ϊ����Ȧ
				break;
			}
			if ((p->spicy == 2 || p->spicy == 3) && (s[i].gethead() == NULL || s[i].isblacksty() == 2) && s[i].getcount() < 10) {
				p->id2 = s[i].getcount();
				s[i].addpig(p);
				s[i].setisblack(2);//����ʼΪ��������Ϊ����Ȧ 0-2
				break;
			}
		}
		number--;
	}
}

void sellpig(Sty2 s[]) {
	if ((month + day / 30 < 3)) {
		cout << "�����ϴγ�Ȧ���ʱ�䲻�����£���������һ��ʱ�䣡" << endl;
		return;
	}
	double sellprice = 0;
	int a = 0, b = 0, c = 0;
	for (int i = 0; i < 100; i++) {
		sellprice += s[i].getprice(a, b, c);
	}
	int temp = getallpig(s), outpignum = allpig - temp;//����ע����������
	money += sellprice;
	int blackpig = 0, blanksty = 0, count = 0;
	for (int i = 0; i < 100; i++) {
		if (s[i].getcount() == 0) {
			blanksty++;
			continue;
		}
		if (s[i].getspicy1())
			blackpig += 10 - s[i].getspicy1();
		else {
			count += 10 - s[i].getcount();
		}
	}
	cout << "δ���ĺ���Ȧ�ɹ���" << blackpig << "ͷ����ʣ���Ȧ��Ϊ��" << blanksty << endl;
	int bpig, lpig, wpig;
	cout << "��ʾ��ÿͷ������1500Ԫ��ÿͷС����800Ԫ��ÿͷ����700Ԫ,��ǰ���" << money << endl;
	cout << "��������㹻��Ľ�ң�����������" << (blackpig + blanksty * 10) << "ͷ����" << count << "ͷС����" << endl;
	cout << "���������뱾�ι���ĺ���С��������������������ܺͻ���������ͬһ��Ȧ�ڣ�";
	cin >> bpig >> lpig >> wpig;
	while (1) {
		if (bpig > (blackpig + 10 * blanksty) || lpig > (count + 10 * blanksty) || wpig > (count + 10 * blanksty) || (lpig + wpig) > count + 10 * blanksty)
			cout << "���������������������������������������" << endl;
		else if (money < (bpig * 1500 + lpig * 800 + 700 * wpig))
			cout << "���㣬����������";
		else if (((blanksty - (bpig - blackpig) / 10) * 10 <= lpig + wpig) && bpig > blackpig)//����Ȧ�޷����»���
			cout << "���������������������������������������" << endl;
		else if (allpig + bpig + lpig + wpig == 1000) {
			cout << "����������Ϸʤ��" << endl;
			exit(0);
		}
		else
			break;
		cin >> bpig >> lpig >> wpig;
	}
	money -= bpig * 1500 - lpig * 800 - wpig * 700;
	allpig += bpig + lpig + wpig;
	cout << allpig << endl;
	buypig(bpig, lpig, wpig, s);
	sbsty(outpignum, sellprice, bpig, lpig, wpig);
	sellcnt++;//ÿ��Ȧһ�μ�1����ʼΪ0��ʱ����Ϊ3����
	while (day >= 30) {
						day -= 30;
						month++;
    }
	month -= 3;
	cin.get();
	cin.get();
	Menu_initgame();
}
void Menu1() {//����˵����һ���˵�
	cout << "\n\n\n\n";
	cout << "            ==============================================================================\n";
	cout << "\n";
	cout << "                                         ������Ϸ                                              \n";
	cout << endl;
	cout << "                      ��ѡ����Ϸ������\n";
	cout << endl;
	cout << "                        1.��ʼ��Ϸ\n";
	cout << endl;
	cout << "                        2.����\n";
	cout << endl;
	cout << "                        3.�˳�\n";
	cout << endl;
	cout << "            ==============================================================================\n";
}
void help() {
	system("cls");//���
	cout << "\n\n\n\n";
	cout << "            ==============================================================================\n";
	cout << "                                         ��Ϸ����                                              \n";
	cout << endl;
	cout << "                      1.��������100����Ȧ��ÿ����Ȧ�����10ͷ��\n";
	cout << endl;
	cout << "                      2.��һ��������Ʒ�֣�����С����ʹ󻨰������к��������������������һ����Ȧ��\n";
	cout << endl;
	cout << "                      3.�ۼۣ�����15Ԫһ�С����7Ԫһ��󻨰���6Ԫһ��\n";
	cout << endl;
	cout << "                      4.��������ʱ����������ģ�ÿͷ������1500Ԫ��ÿͷС����800Ԫ��ÿͷ����700Ԫ;����������������о�\n";
	cout << endl;
	cout << "                        ��\n";
	cout << endl;
	cout << "                      5.�涨ÿ3���£�����Ҫ��Ȧһ�������������س���150��ĺ���������1��ģ�ͬʱ����һ�����̶�\n";
	cout << endl;
	cout << "                      6.��ʼ�������200000��ң�500ͷ�����������Ȧ�����ص��������\n";
	cout << endl;
	cout << "                      7.�ɸ�����Ȧ�Լ����̵ı�Ų�ѯ��Ӧ�ľ�����Ϣ����Ȧ����0-99��ţ����̱��0-9\n";
	cout << endl;
	cout << "                      8.������ĳһֻ�������������������չ�����ǣ�ͬһ����Ȧ����ÿ�챻��Ⱦ������50 % ��������Ȧ����ÿ\n";
	cout << endl;
	cout << "                        �챻��Ⱦ�ļ�����15%�������ڵ���Ȧ������Ⱦ�����������������������޼�ֵ\n";
	cout << endl;
	cout << "                      9.��Ӯ������������������Ϊʤ��\n";
	cout << endl;
	cout << "                      10.�˳���Ϸǰ�ǵñ�����Ϸ\n";
	cout << endl;
	cout << "            ==============================================================================\n";
	
	Menu1();
}


void check() {//��ѯ����
	system("cls");//���
	cout << "\n\n\n\n";
	cout << "            ==============================================================================\n";
	cout << "                                       ��ѯ                                                   \n";
	cout << endl;
	cout << "                                   ��ѡ�������            \n";
	cout << endl;
	cout << "                                 1.��ѯĳ��Ȧ�������������            \n";
	cout << "                                 2.��ѯĳ��Ȧĳͷ���״̬��Ϣ            \n";
	cout << "                                 3.ͳ��ÿ��������������أ�����ʱ��ֲ�            \n";
	cout << "                                 4.��ѯ������������ۺ͹����¼         \n";
	cout << "                                 5.��ӡ��ǰ����������Ϣ          \n";
	cout << "                                 6.������Ϸ����         \n";
	cout << endl;
	cout << "            ==============================================================================\n";
}void Menu_deal() {//��������
	system("cls");//���
	cout << "\n\n\n\n\n\n";
	cout << "            ==============================================================================\n";
	cout << "                                      ��������                                                \n";
	cout << endl;
	cout << "                                   ��ѡ�������            \n";
	cout << endl;
	cout << "                                 1.��������           \n";
	
	
	cout << "                                2.������Ϸ���沢���¿�ʼ��Ϸ         \n";
	cout << endl;
	cout << "            ==============================================================================\n";
}
int main() {

	Sty2 s[100];
	Menu1();//��ʼ����
	int flag ;
	ifstream infile(("stys.txt"), ios::in);
	infile >> flag;
	if (flag == 0) {

		Menustys(s);//��ʼ����Ϸ����
		
	}
	else {
		Menustybyfile(s);//������������Ϣ�Լ�ÿֻ�����Ϣ
	}
	infile.close();
	
	int game;
	cout << "��������Ҫ�Ĳ���(�������ǰ������)��" << endl;
	cin >> game;
	do {
		switch (game) {
		case 1: {
			Menu_initgame();
			int option;
			cin >> option;
			do {
				switch (option)
				{
				case 1: {
					check();
					int choice;
					cin >> choice;//������ѯ����
					do {
						switch (choice)
						{
						  case 1: {
							int num;
							cout << "��������Ȧ�ţ�";
							cin >> num;
						
							cout << "����Ȧ��" << s[num].getcount() << "ͷ�������к���" << s[num].getspicy1() << "ͷ��С����" << s[num].getspicy2() << "ͷ������" << s[num].getspicy3() << "ͷ" << endl;
							break;
						  }
						  case 2: {
							int num1, num2;
							cout << "��������Ȧ�ţ������0-99" << endl;
							cin >> num1;
							while (1) {
								if (num1 >= 0 && num1 < 100 && s[num1].getcount() != 0)
									break;
								else {
									cout << "������������Ȧ�ţ�����ȦΪ��" << endl;
								}
								cin >> num1;
							}
							cout << "����Ȧ����" << s[num1].getcount() << "ͷ����������ı�ţ�0-9����";
							cin >> num2;
							while (1) {
								if (!s[num1].search(num2)) {
									cout << "�������ڣ������Ѿ���Ȧ�����������Ź������������룺";
									cin >> num2;
								}
								else
									break;
							}
							cout << "����Ϊ��";
							if (s[num1].getspicy(num2) == 1)cout << "����";
							if (s[num1].getspicy(num2) == 2)cout << "С����";
							if (s[num1].getspicy(num2) == 3)cout << "����";
							cout << "����Ϊ��" << s[num1].getweight(num2) << "kg,����ʱ��Ϊ��";
													
							int month = s[num1].getgrowmonth(num2), day = s[num1].getgrowday(num2);
							while (day >= 30) {
								month++;
								day -= 30;
							}
							if (month > 0)
								cout << month << "����" << day << "��" << endl;
							else
								cout<< day << "��" << endl;
							break;
						  }
						  case 3:printdetail(s);
							  break;
						 
						  case 4: {

							readsbsty();
							break;
						  }
						  case 5: {
							for (int i = 0; i < 100; i++) {
								cout << i << "��Ȧ�� ";
								s[i].print();

							}
							break;
						  }
						  default:break;

						}
						if (choice == 6)
							break;
						cin >> choice;
					}while (1);
					Menu_initgame();
					break;
				}
				case 2: {
					sellpig(s);
					break;

				}
				case 3: {
					for (int i = 0; i < 100; i++) {
						s[i].clearsty();
					}
					Menustys(s);//������Ϸ��ζ��������Ϸ���������ԭ��������ô��Ȧ��Ϣ�ȶ���Ҫɾ��
					//һ�������ļ���һ�����ڼ�¼ ���������������Ϣ��һ�����Լ�¼ʱ�䣬��ң���һ����¼��Ȧ��¼
					
					Menu_initgame();
					break;
				}
				case 4: {
					//������Ϸ������ǰ��״̬���������������ļ�����Ҫ�����г�Ȧ����������
					savefile(s);
					savecomprehensive();
					break;
				}
				case 5: {
					for (int i = 0; i < 100; i++) {
						s[i].next(1);
					}
					day++;
				
					Menu_initgame();
					break;
				}
				case 6: {
					for (int i = 0; i < 100; i++) {
						s[i].next(30);
					}
				
					month++;
					Menu_initgame();
					break;

				}
				case 7: {
					cout << "�����뷢�����ߵ���Ȧ��" << endl;
					int num4;
					cin >> num4;
					deadday(s, num4);
					Menu_deal();
					int num5;
					cin >> num5;
					switch (num5)
					{
					    case 1: {
							dealdisease(s, num4);
							Menu_initgame();
							break;
					    }

						       
						case 2: {
							for (int i = 0; i < 100; i++) {
								s[i].clearsty();
							}
							Menustys(s);
							Menu_initgame();
							break;
						}
					    default:
						     break;
					}
					
					break;

				}
				default:break;//�����˳���Ϸ���棬���س�ʼҳ��
				}
				if (option == 8)
					break;
				
				cin >> option;

			} while (1);
			break;

		}
		case 2: {
			help();
			break;
		}

		}
		if (game == 3)
			exit(0);
		else
			cin >> game;
	} while (1);
	return 0;
}