#include "priority_queue.h"

void test1()
{
	//Ĭ���Ǵ��
	vector<int> v;
	v.resize(10, 1);
	tao::priority_queue<int,vector<int>> pq;
	//priority_queue<int,vector<int>,less<int>> pq Ĭ���Ǵ��
	//priority_queue<int, vector<int>, greater<int>> pq;��������С��

	pq.push(1);
	pq.push(2);
	pq.push(3);
	pq.push(4);
	pq.push(5);
	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
	
	//�º���--->������������һ��ʹ�ñ��ʾ������������������()
	

}
void test2()
{

	tao::priority_queue<Data*,vector<Data*>,tao::LessPData> pq;//Ĭ���Ǵ��
	//tao::priority_queue<Data, vector<Data>, tao::Greater<Data>> pq;
	//Ҳ��������
	pq.push(new Data(2023, 1, 1));
	pq.push(new Data(2023, 1, 2));
	pq.push(new Data(2023, 1, 3));
	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
	
}
int main()
{

	test2();

}