#include "Sty2.h"
#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<stdlib.h>
#include<iomanip>
using namespace std;
double money;
int month, day;
int allpig;
int sellcnt;//出圈次数
int cnt1, cnt2, cnt3;//各类猪的总数
int dead1, dead2, dead3, deadall;//发生瘟疫时处理后死亡的数量
int getallpig(Sty2 s[]) {//获得整个猪场的猪的总数量
	int allcount = 0;
	for (int i = 0; i < 100; i++) {
		allcount += s[i].getcount();
	}
	return allcount;
}

void savesty(Sty2 s,ofstream &savefile) {//将某一猪圈内所有猪的信息存入文件中
	if (s.head == NULL) {
		savefile << '$' << endl;//getspicy(i)为'$'代表当前猪圈为空猪圈
		return;
	}
	else {
		pig * p =s.head;

		savefile << s.cntall << endl;
		while (p) {
			savefile <<  s.getspicy(p->id2) << s.getweight(p->id2) << s.getgrowmonth(p->id2)  << s.getgrowday(p->id2) << endl;//有问题，就是标号对不上

			p = p->next;
		}
	}
}
void Menustybyfile(Sty2 s[]) {
	ifstream getinfo;
	getinfo.open("comprehensive.txt");//789.txt
	getinfo >> allpig >> money >> month >> day >> sellcnt;//写入文件中总的数量，金币数，饲养时间，卖出次数
	getinfo.close();
	ifstream read;
	read.open("stys.txt");//123.txt
	if (!read) {
		cout << "读取保存的数据失败";
		exit(0);
	}
	int t, cntnum;
	pig * p;  //从文件读取整个猪场每头猪的信息，'$'代表空猪圈
	read >> t;//t标志位
	for (int i = 0; i < 100; i++) {
		read >> cntnum;
		for (int j = 0; j < cntnum; j++) {
			p = new pig;
			//p->id2 = j;
			read >> p->id2;
			read >> p->spicy;
			if (p->spicy == '$') {
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
//买猪
void buypig(int bpig, int lpig, int wpig, Sty2 s[]) {//前面三个参数为买入的三种猪的数量，有问题待改进
	while (bpig--) {//买入数量按道理是可以全部加入猪场的
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
				if (lpig > 0 && s[i].getcount() <= aver) {//保证平均买入，方法比较粗糙，待改进
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



void savepig() {
	ofstream save;
	save.open("comprehensive.txt");//猪场总体信息，金币数，猪的总数，开办时间
	if (!save) {
		cout << "无法打开，保存全局变量失败" << endl;
	}
	else {
		save << "猪场总猪数" << "   金币数" << "  猪场开办时间(月，日)" <<"出圈次数"<<endl;
		save <<allpig  << money << month << day    << sellcnt<<endl;
		cout << "保存成功" << endl;
		save.close();
	}

}

/*（1）可任意查询当前某一猪圈的猪的数量和种类；
（2）可任意查询当前某一猪圈某头猪的状态信息；
（3）可任意统计当前猪场每个品种猪的数量和体重、饲养时间分布情况；（到此70起评）
（4）可任意查询近5年猪的销售记录和猪崽儿的购入记录（记录用文件形式存储）；*/
void sbsty(int sellpignum, double sellprice, int bpig, int lpig, int wpig) {//记录出圈信息,卖出买入的各类总数，金额
	ifstream testin;
	testin.open("sbsty.txt");
	char flag;
	testin >> flag;
	if (flag == '#') {
		testin.close();
		ofstream testout;
		testout.open("sbsty.txt");//有出圈记录后第一个字符变为$,然后在原有记录上添加
		testout << '$';
		testout.close();
	}
	else {
		testin.close();
	}
	ofstream save("sbsty.txt", ios::app);//增补方式，每次写入的数据都加到尾端
	//卖出数量，卖出价格，买入价格，买入的三类猪数量
	save << sellcnt;//出圈次数
	save << sellpignum << "  " << sellprice << "  " << bpig << "  " << lpig << "  " << wpig << "  " << 2000 * bpig + 1500 * lpig + 300 * wpig << endl;;
	save.close();
}
void readsbsty() {
	ifstream read;
	read.open("sbsty.txt");//出圈信息文件
	if (!read) {
		cout << "打开出圈信息文件失败";
		exit(0);
	}
	char flag;
	read >> flag;
	if (flag == '#') {
		cout << "无记录" << endl;
		return;
	}
	int times, outpigs, sellprice, bpig, lpig, wpig, cost;//memlast;// memlast是啥玩意
	while (!read.eof()) {
		read >> times;//对应sellcnt
		/* (memlast == times) {
			flag = 1;
			continue;
		}*/
		//memlast = times;
		read >> outpigs >> sellprice >> bpig >> lpig >> wpig >> cost;
		cout << "第" << (times+3) / 4 + 1 << "年";
		cout << "第" << ((times +9)% 12 + 1) << "个月" << endl;//输出时间
		cout << "出圈猪数: " << outpigs << "   获得收益： " << sellprice << "  买入黑猪数： " << bpig << "  买入小花猪数： " << lpig << "  买入大花猪数 " << wpig << " 共花费 " << cost << endl;
	}
}

void savefile(Sty2 s[]) {
	ofstream savefile;
	savefile.open("stys.txt");//保存了整个猪场每只猪的信息
	if (!savefile) {
		cout << "打开保存文件失败";
		exit(0);
	}
	savefile << 1 << endl;//初始化为0，存入数据后则变为1
	for (int i = 0; i < 100; i++) {//将信息存入文件中
	    savesty(s[i],savefile);
	}
	savefile.close();
}
int deadday(Sty2 s[],int id) {/*养猪场某一只猪得了猪瘟，猪瘟的扩展几率是，同一个猪圈的猪每天被传染几率是50%，
					   相邻猪圈的猪每天被传染的几率是15%，不相邻的猪圈的猪不传染。编写程序模拟多久后养猪场的猪死光光。*/
					   //利用已有的感染处理函数递归或许可以
	s[id].flag = true;
	int deadall = 0; int day;
	int sum = allpig;
	for (day = 1; deadall < sum; day++) {
		for (int i = 0; i < 99; i++) {//每天更新每个猪圈的数量
			if (s[i].flag == 2) {
				//0表示未感染，1表示将被传染，2表示已染上
				//先更新每天每个猪圈的感染情况，最后计算这一天的死亡数
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

	return day;
}
void chuli(Sty2 s[], int id) {
	int t1 = 0;
	int t2 = 0;
	if (s[id].cnt1 != 0) {//黑猪圈
		dead1 += int(s[id].cnt1*0.15 + 0.5);//存活数量向下取整 ,死亡数向上取
		s[id].cntall = s[id].cnt1 = int(s[id].cnt1 *0.85);
	}
	else
	{    //这是处理相邻猪圈的函数，那么出事猪圈在上一函数中自行解决
		//若白猪混合，则默认剩余总数按比例向下取整，然后先计算小白猪剩余总数，按总占比计算，剩余死亡数再分配给大白猪
		deadall = int(s[id].cntall*0.15 + 0.5);
		t1 = int(double(s[id].cnt1*deadall) / s[id].cntall + 0.5);//小白猪死亡的数量
		t2 = deadall - t1;//大白猪死亡数量
		dead2 += t1;
		dead3 += t2;
		s[id].cntall = s[id].cntall - deadall;
		s[id].cnt1 = s[id].cnt1 - t1;
		s[id].cnt2 = s[id].cnt2 - t2;
	}
}
void dealdisease(Sty2 s[],int id) {//得瘟疫的猪杀掉，未得的继续饲养，并更新猪场以及猪圈相关信息
	dead1 = dead2 = dead3 = deadall = 0;//最后应该可以提炼出处理黑，白猪圈的一个函数再调用
	int t1 = 0;
	int t2 = 0;
	if (s[id].getcount() != 0) {//黑猪圈
		dead1 = (s[id].cntall + 1) / 2;//存活数量向下取整 ,死亡数向上取
		s[id].cntall = s[id].cnt1 = s[id].cnt1 / 2;
	}

	else {
		deadall = int(s[id].cntall*0.5 + 0.5);
		t1 = int(double(s[id].cnt1*deadall) / s[id].cntall + 0.5);//小白猪死亡的数量
		t2 = deadall - t1;
		dead2 += t1;
		dead3 += t2;
		s[id].cntall = s[id].cntall - deadall;
		s[id].cnt1 = s[id].cnt1 - t1;
		s[id].cnt2 = s[id].cnt2 - t2;
	}

	if (id == 0)
	{
		chuli(s,1);
	}
	else if (id == 99) {
		chuli(s,98);
	}
	else {
		chuli(s,id - 1);
		chuli(s,id + 1);
	}
	deadall = dead1 + dead2 + dead3;
}

//可任意统计当前猪场每个品种猪的数量和体重、饲养时间分布情况；
void Menustys(Sty2 s[]) {//初始化游戏条件，确定初始猪的数量，种类，体重以及猪圈分配和金币数
	allpig = 500;
	money = 20000;
	month = 0;
	day = 0;
	sellcnt = 0;
	ofstream f;
	f.open("stys.txt");  //123.txt
	f << 1;//表示猪数量为0，初始状态的猪场
	f.close();
	f.open("sbsty.txt");  //456.txt
	f << '#';//出圈记录为空
	f.close();
	pig * p;
	int number = 500;
	srand((unsigned)time(NULL));
	while (number) {//为每头猪分配猪圈
		p = new pig;
		p->spicy = rand() % 3 + 1;
		p->weight = rand() % 30 + 20;
		p->growmonth = 0;
		p->growday = 0;
		for (int i = 0; i < 100; i++) {
			if (p->spicy == 1 && (s[i].isblacksty() == 1 || s[i].gethead() == NULL) && s[i].getcount() < 10) {
				p->id2 = s[i].getcount();
				s[i].addpig(p);
				s[i].setisblack(1);//若初始为空则设置为黑猪圈
				break;
			}
			if ((p->spicy == 2 || p->spicy == 3) && (s[i].gethead() == NULL || s[i].isblacksty() == 2) && s[i].getcount() < 10) {
				p->id2 = s[i].getcount();
				s[i].addpig(p);
				s[i].setisblack(2);//若初始为空则设置为白猪圈 0-2
				break;
			}
		}
	}
}
void Menu1() {//输出菜单项，第一个菜单
	cout << "\n\n\n\n\n\n";
	cout << "            ==============================================================================\n";
	cout << "\n";
	cout << "                                         养猪游戏                                              \n";
	cout << endl;
	cout << "                      请选择游戏操作：\n";
	cout << endl;
	cout << "                        1.开始游戏\n";
	cout << endl;
	cout << "                        2.帮助\n";
	cout << endl;
	cout << "                        3.退出\n";
	cout << endl;
	cout << "            ==============================================================================\n";
}
void Menu_initgame() {//开始游戏界面的子菜单
	system("cls");//清空
	cout << "\n\n\n\n\n\n";
	cout << "            ==============================================================================\n";
	cout << "                         我的猪场                                                        \n";
	cout << "                           1.查询\n";
	cout << "                           2.出圈并购猪\n";
	cout << "                           3.重新游戏\n";
	cout << "                           4.保存游戏\n";
	cout << "        5.下一天                   6.下个月\n";
	cout << endl;
	cout << "        当前金币数：" << money << "  总猪数：" << allpig << "饲养时间：";
	if (month > 0)cout << month << "个月";
	if (day >= 0)cout << day << "天";
	cout << endl;
	cout << "            ==============================================================================\n";
}
void check() {//查询界面
	system("cls");//清空
	cout << "\n\n\n\n\n\n";
	cout << "            ==============================================================================\n";
	cout << "                                       查询                                                   \n";
	cout << endl;
	cout << "                                   请选择操作：            \n";
	cout << endl;
	cout << "                                 1.查询某猪圈猪的数量和种类            \n";
	cout << "                                 2.查询某猪圈某头猪的状态信息            \n";
	cout << "                                 3.统计每种猪的数量，体重，饲养时间分布            \n";
	cout << "                                 4.查询近五年猪的销售和购入记录         \n";
	cout << "                                 5.打印当前猪场的所有信息          \n";
	cout << "                                 6.返回游戏界面         \n";
	cout << endl;
	cout << "            ==============================================================================\n";
}

int main() {

	Sty2 s[100];
	Menu1();
	int flag ;
	ifstream infile(("stys.txt"), ios::in);
	infile >> flag;
	cout << flag << endl;
	if (flag == 0) {
		cout << flag << endl;

		Menustys(s);//初始化游戏条件
		cout << "初始化游戏条件";
		cout << allpig << money << endl;
	}
	else {
		Menustybyfile(s);//读入猪场总体信息以及每只猪的信息
	}
	infile.close();
	//allpig = getallpig(s);
	int game;
	cout << "请输入你要的操作(输入操作前的数字)：" << endl;
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
					cin >> choice;//决定查询内容
					do {
						switch (choice)
						{
						  case 1: {
							int num;
							cout << "请输入猪圈号：";
							cin >> num;
							cout << "此猪圈有" << s[num].getcount() << "头猪，其中有黑猪" << s[num].getspicy1() << "头，小花猪" << s[num].getspicy2() << "头，大花猪" << s[num].getspicy3() << "头" << endl;
							break;
						  }
						  case 2: {
							int num1, num2;
							cout << "请输入猪圈号，编号在0-99" << endl;
							cin >> num1;
							while (1) {
								if (num1 >= 0 && num1 < 100 && s[num1].getcount() != 0)
									break;
								else {
									cout << "请重新输入猪圈号，该猪圈为空" << endl;
								}
							}
							cout << "此猪圈共有" << s[num1].getcount() << "头猪，请输入猪的编号（0-9）：";
							cin >> num2;
							while (1) {
								if (!s[num1].search(num2)) {
									cout << "此猪不存在，可能已经出圈，可能输入编号过大，请重新输入：";
									cin >> num2;
								}
								else
									break;
							}
							cout << "此猪为：";
							if (s[num1].getspicy(num2) == 1)cout << "黑猪";
							if (s[num1].getspicy(num2) == 2)cout << "小花猪";
							if (s[num1].getspicy(num2) == 3)cout << "大花猪";
							cout << "体重为：" << s[num1].getweight(num2) << "kg,饲养时间为：";
							/**/							 int month = s[num1].getgrowmonth(num2), day = s[num1].getgrowday(num2);
							while (day >= 30) {
								month++;
								day -= 30;
							}
							if (month > 0)cout << month << "个月" << day << "天" << endl;
							break;
						  }
						  case 3:break;
						  case 4: {

							readsbsty();
							break;
						  }
						  case 5: {
							for (int i = 0; i < 100; i++) {
								cout << i << "号圈， ";
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
					if (month + day / 30 < 3*(sellcnt+1)) {
						cout << "距离上次出圈后的时间不足三月，请再饲养一段时间！" << endl;
						break;
					}
					double sellprice = 0;
					int a = 0, b = 0, c = 0;
					for (int i = 0; i < 100; i++) {
						sellprice += s[i].getprice(a,b,c);
					}
					int temp = getallpig(s), outpignum = allpig - temp;//这里注意卖出的猪
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
					cout << "未满的黑猪圈可购入" << blackpig << "头黑猪，剩余空圈数为：" << blanksty << endl;
					int bpig, lpig, wpig;
					cout << "提示：每头黑猪崽1500元，每头小花猪800元，每头大花猪700元,当前余额" << money << endl;
					cout << "如果您有足够多的金币，建议您购买" << (blackpig + blanksty * 10) << "头黑猪，" << count << "头小白猪" << endl;
					cout << "请依次输入本次购入的黑猪，小花猪，大花猪的数量（黑猪不能和花猪饲养在同一猪圈内）";
					cin >> bpig >> lpig >> wpig;
					while (1) {
						if (bpig > (blackpig + 10 * blanksty) || lpig > (count + 10 * blanksty) || wpig > (count + 10 * blanksty) || (lpig + wpig) > count + 10 * blanksty)
							cout << "购入猪的数量超过猪场的容纳能力，请重新输入" << endl;
						else if (money < (bpig * 1500 + lpig * 800 + 700 * wpig))
							cout << "余额不足，请重新输入";
						else if (((blanksty - (bpig - blackpig) / 10) * 10 <= lpig + wpig) && bpig > blackpig)//空猪圈无法放下花猪
							cout << "购猪不合理，黑猪不能与另两种猪混养，请重新输入" << endl;
						else if (allpig + bpig + lpig + wpig == 1000) {
							cout << "养满猪场，游戏胜利" << endl;
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
					sellcnt++;//每出圈一次加1，初始为0，时间间隔为3个月
					while (day >= 30) {
						day -= 30;
						month++;
					}
					//month -= 3;
					cin.get();
					cin.get();
					Menu_initgame();
					break;

				}
				case 3: {
					for (int i = 0; i < 100; i++) {
						s[i].clearsty();
					}
					Menustys(s);
					Menu_initgame();
					break;
				}
				case 4: {
					savefile(s);
					savepig();
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
				default:break;
				}
				cin >> option;

			} while (1);
			break;

		}
		case 2: {
			cout << "输赢条件：养满整个猪场即为胜利" << endl;
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