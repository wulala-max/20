#include<iostream>
using namespace std;
//����PIG�࣬�����������أ�ʱ�䣬����,������Ȧ
//�����и������أ�������Ϣ������������ʼ���أ�Ʒ�֣�������Ȧ��������ɣ�


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
	int variety;//0�������1����С������2����󻨰���
	int id;//������Ȧ��
};


//��Ȧ��Ϊһ���ṹ��,�ܹ�100����Ȧ
struct sty
{
	int num, id;//��������Լ���Ȧ��
	Pig  a[10];//10ֻ�����Ϣ
	sty * next;//ǰ����Ȧ
	sty * pre;
}stys[100];
//ͳ�������������أ�����ʱ��ֲ�����Լ���ǰ��ÿ��Ʒ���������
struct dofpig {
	int count;
	int t[4];//����ʱ�䣬3�����ڣ�6�����ڣ�9�����ڣ�һ������
	int w[7];//30,40,50,60,70,75
}piggery[3];//p[0]p[1]p[2]���α�ʾ����С���������
//�ȳ�ʼ���������ÿ�γ�������������������

void init() {

}



//����������ۼۼ��㲢��������
double sale() {
	double sum;

}

//�����в������̲���������
void add() {

}

int main() {
	double sale;

	return 0;
}