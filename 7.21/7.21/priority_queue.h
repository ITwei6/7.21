#pragma once
#include <iostream>
#include <vector>
//#include <queue>
using namespace std;

class Data
{
	//析构也不用写
	friend ostream& operator<<(ostream& out, const Data& d);
public:
	
	Data(int year = 1, int month = 1, int day = 1)//构造函数要写，拷贝构造函数不用写，赋值重载不用写
	{
		_year = year;
		_month = month;
		_day = day;
	}
	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
	Data(const Data& d)
	{

		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	bool operator<(const Data& d);
	bool operator==(const Data& d);
	bool operator<=(const Data& d);
	bool operator>(const Data& d);
	bool operator>=(const Data& d);
	bool operator!=(const Data& d);
	Data operator++();//前置++
	Data operator++(int);//后置++
	int GetMonDay(int year, int month);
	Data& operator+=(int day);
	Data operator+(int day);
	Data& operator-=(int day);
	Data operator-(int day);
	int operator-(Data& d);
private:
	int _year;
	int _month;
	int _day;
};
ostream& operator<<(ostream& out, const Data& d)
{
	out <<d._year<<"-" << d._month<<"-"<<d._day ;
	return out;
}
bool Data:: operator<(const Data& d)
{
	if (_year < d._year)
	{
		return true;
	}
	else if (_year == d._year && _month < d._month)
	{
		return true;
	}
	else if (_year == d._year && _month == d._month && _day < d._day)
	{
		return true;
	}
	return false;

}
bool Data::operator==(const Data& d)
{
	return _year == d._year
		&& _month == d._month
		&& _day == d._day;
}
bool Data::operator<=(const Data& d)//直接复用上面的
{
	return *this < d || *this == d;
}
bool Data::operator>(const Data& d)
{
	return !(*this <= d);
}

bool Data::operator>=(const Data& d)
{
	return !(*this < d);
}
bool Data::operator!=(const Data& d)
{
	return !(*this == d);
}

int Data::GetMonDay(int year, int month)
{
	static int monday[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };//频繁调用
	/*if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)&&month==2)*/
	if (month == 2 && (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
	{
		return 29;
	}
	else
		return monday[month];
}
//Data& Data::operator+=(int day)//用+复用+=-最好先实现+= 再复用实现 +
//{
//	*this=*this + day;
//	
//	return *this;
//}
Data& Data::operator+=(int day)
{
	if (day < 0)
	{
		return *this -= -day;
	}
	_day += day;
	while (_day > GetMonDay(_year, _month))
	{
		_day -= GetMonDay(_year, _month);
		++_month;
		if (_month == 13)
		{
			++_year;
			_month = 1;
		}
	}
	return *this;
}
Data Data::operator+(int day)
{
	Data tmp(*this);//拷贝一份，让tmp返回，*this没有改变
	tmp._day += day;
	while (tmp._day > GetMonDay(tmp._year, tmp._month))
	{
		tmp._day -= GetMonDay(tmp._year, tmp._month);
		++tmp._month;
		if (tmp._month == 13)
		{
			++_year;
			tmp._month = 1;
		}
	}
	return tmp;
}
//Data Data::operator+(int day)  //+ 复用+=
//{
//	Data tmp(*this);//拷贝一份，让tmp返回，*this没有改变
//	tmp += day;//复用+=重载函数 
//	return tmp;
//}
Data Data::operator++()//前置++运算符重载
{
	*this += 1;
	return *this;
}
Data Data::operator++(int)//后置++运算符重载
{
	Data tmp(*this);
	*this += 1;
	return tmp;
}
Data& Data::operator-=(int day)
{
	if (day < 0)
	{
		return *this += -day;
	}
	_day -= day;
	while (_day <= 0)
	{
		--_month;
		if (_month == 0)
		{
			--_year;
			_month = 12;
		}
		_day += GetMonDay(_year, _month);
	}
	return *this;
}
Data Data::operator-(int day)
{
	Data tmp(*this);
	tmp -= day;
	return tmp;
}
//d1 - d2
int Data::operator-(Data& d)
{
	Data max = *this;
	Data min = d;
	int flag = 1;

	if (*this < d)
	{
		max = d;
		min = *this;
		flag = -1;
	}
	int n = 0;
	while (min != max)
	{
		++min;
		++n;
	}
	return n * flag;
}

namespace tao
{
	template<class T, class container=vector<T>,class compare=Less<T>>//通过第三个仿函数来控制比较,进而控制大堆还是小堆
	//默认的那种方式是写死了，而这种方法通过仿函数
	//通过模板参数来控制比较类型，比较类型又通过重载()
	class priority_queue
	{
	private:
		compare com;//比较泛型---灵活比较
		void Adjustdown(int parent)
		{
			//首先找到左右孩子中较大的那一个
			int child = parent * 2 + 1;
		     //默认左孩子是小的
			if (child + 1 < _con.size() && com(_con[child] ,_con[child + 1]))
			{
				++child;
			}

			while (child<_con.size())
			{
				//比较父节点和孩子结点
				if ( com(_con[parent] , _con[child]))
				{
					swap(_con[child], _con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
		void Adjustup(int child)//向上调整只要一直顺着双亲向上调整即可
		{
			//首先确定父节点位置
			int parent = (child - 1) / 2;

			while (child>0)
			{
				//然后比较父节点与这个结点的大小--默认大堆
				if (com(_con[parent] , _con[child]))
				{
					//不需要管另一个子结点(如何有的话，因为child之前都是堆，满足堆的性质，比如大堆，那么子结点一定小于父节点的)
					swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
		}
		}
	public:
		//构造函数--用迭代区间来构造函数
		//这个迭代器可以写成模板
		template<class InputIterator>
		priority_queue(InputIterator begin,InputIterator last)
		{
			//第一首先将数据插入进去
			while (begin != last)
			{
				_con.push_back(*begin);
				++begin;
			}
			//第二需要建堆，默认建的是大堆--利用向下调整算法建堆
			//从最后一个叶子结点的父亲开始向下调整
			for (int i = (_con.size() - 1 - 1) / 2; i >= 0; i--)
			{
				Adjustdown(i);
			}
		}
		priority_queue()
		{}
		void pop()
		{
			swap(_con[0], _con[_con.size() - 1]);
			//里面封装着容器，直接用容器删除最后一个数据
			_con.pop_back();

			Adjustdown(0);
		}
		void push(const T& val)
		{
			_con.push_back(val);
			//使用向上调整算法，调整堆
			Adjustup(_con.size()-1);
		}
		T& top()
		{
			return _con[0];
		}
		bool empty()
		{
			return _con.empty();
		}
		size_t size()
		{
			return _con.size();
		}
	private:
		container _con;
		//容器适配器，封装了一个容器,但优先级队列不只是简单的容器封装还对容器里的数据进行了加工。插入尽量的数据还要利用算法进行调整
	};
	//仿函数/函数对象？
	template<class T>
	class Less
	{
	public:
		
		bool operator()( T& x, T& y)//重载()  也是一种泛型， 对控制比较的泛型
		{
			return x < y;
		}
	};
	template<class T>
	class Greater
	{
	public:
		
		bool operator()( T& x,  T& y)//重载()  也是一种泛型， 对控制比较的泛型
		{
			return x > y;
		}
	};
	class LessPData
	{
	public:

		bool operator()( Data* d1, const Data* d2)//重载()  也是一种泛型， 对控制比较的泛型
		{
			return  *d1<*d2;
		}
	};
};