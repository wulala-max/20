#include<iostream>
using namespace std;
//构建PIG类，数据域有体重，时间，种类,所属猪圈
//方法有更新体重，入栏信息包括数量，初始体重，品种，所属猪圈，随机生成，


class Pig
{
public:
	Pig() {
	     
	
	
	};
	~Pig() {};
	double getTime() {
		return this->time;
	}
	double getWeight() {
		return this->weight;
	}
	int getVariety() {
		return this->variety;
	}
	int getNum() {
		return this->id;
	}
private:
	double time;
	double weight;
	int variety;//0代表黑猪，1代表小花白猪，2代表大花白猪；
	int id;//所属猪圈数
};


//猪圈作为一个结构体,总共100个猪圈
struct sty
{
	int num, id;//猪的数量以及猪圈号
	Pig  a[10];//10只猪的信息
	sty * next;//前后猪圈
	sty * pre;
}stys[100];
//统计整个猪场的体重，饲养时间分布情况以及当前猪场每个品种猪的数量
struct dofpig {
	int count;
	int t[4];//饲养时间，3个月内，6个月内，9个月内，一年以上
	int w[7];//30,40,50,60,70,75
}piggery[3];//p[0]p[1]p[2]依次表示黑猪，小白猪，大白猪
//先初始化猪场情况，每次出入栏后更新猪场整体情况

void init() {

}



//猪出栏总体售价计算并更新数据
double sale() {
	double sum;

}

//往猪场中补充猪崽并更新数据
void add() {

}

int main() {
	double sale;

	return 0;
}