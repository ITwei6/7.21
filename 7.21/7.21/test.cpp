#include "priority_queue.h"

void test1()
{
	//默认是大堆
	vector<int> v;
	v.resize(10, 1);
	tao::priority_queue<int,vector<int>> pq;
	//priority_queue<int,vector<int>,less<int>> pq 默认是大堆
	//priority_queue<int, vector<int>, greater<int>> pq;这样才是小堆

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
	
	//仿函数--->类对象可以像函数一样使用本质就是类里重载了运算符()
	

}
void test2()
{

	tao::priority_queue<Data*,vector<Data*>,tao::LessPData> pq;//默认是大堆
	//tao::priority_queue<Data, vector<Data>, tao::Greater<Data>> pq;
	//也就是升序
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