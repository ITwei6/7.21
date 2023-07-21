#pragma once
#include <iostream>
#include <vector>
//#include <queue>
using namespace std;

class Data
{
	//����Ҳ����д
	friend ostream& operator<<(ostream& out, const Data& d);
public:
	
	Data(int year = 1, int month = 1, int day = 1)//���캯��Ҫд���������캯������д����ֵ���ز���д
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
	Data operator++();//ǰ��++
	Data operator++(int);//����++
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
bool Data::operator<=(const Data& d)//ֱ�Ӹ��������
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
	static int monday[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };//Ƶ������
	/*if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)&&month==2)*/
	if (month == 2 && (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
	{
		return 29;
	}
	else
		return monday[month];
}
//Data& Data::operator+=(int day)//��+����+=-�����ʵ��+= �ٸ���ʵ�� +
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
	Data tmp(*this);//����һ�ݣ���tmp���أ�*thisû�иı�
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
//Data Data::operator+(int day)  //+ ����+=
//{
//	Data tmp(*this);//����һ�ݣ���tmp���أ�*thisû�иı�
//	tmp += day;//����+=���غ��� 
//	return tmp;
//}
Data Data::operator++()//ǰ��++���������
{
	*this += 1;
	return *this;
}
Data Data::operator++(int)//����++���������
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
	template<class T, class container=vector<T>,class compare=Less<T>>//ͨ���������º��������ƱȽ�,�������ƴ�ѻ���С��
	//Ĭ�ϵ����ַ�ʽ��д���ˣ������ַ���ͨ���º���
	//ͨ��ģ����������ƱȽ����ͣ��Ƚ�������ͨ������()
	class priority_queue
	{
	private:
		compare com;//�ȽϷ���---���Ƚ�
		void Adjustdown(int parent)
		{
			//�����ҵ����Һ����нϴ����һ��
			int child = parent * 2 + 1;
		     //Ĭ��������С��
			if (child + 1 < _con.size() && com(_con[child] ,_con[child + 1]))
			{
				++child;
			}

			while (child<_con.size())
			{
				//�Ƚϸ��ڵ�ͺ��ӽ��
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
		void Adjustup(int child)//���ϵ���ֻҪһֱ˳��˫�����ϵ�������
		{
			//����ȷ�����ڵ�λ��
			int parent = (child - 1) / 2;

			while (child>0)
			{
				//Ȼ��Ƚϸ��ڵ���������Ĵ�С--Ĭ�ϴ��
				if (com(_con[parent] , _con[child]))
				{
					//����Ҫ����һ���ӽ��(����еĻ�����Ϊchild֮ǰ���Ƕѣ�����ѵ����ʣ������ѣ���ô�ӽ��һ��С�ڸ��ڵ��)
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
		//���캯��--�õ������������캯��
		//�������������д��ģ��
		template<class InputIterator>
		priority_queue(InputIterator begin,InputIterator last)
		{
			//��һ���Ƚ����ݲ����ȥ
			while (begin != last)
			{
				_con.push_back(*begin);
				++begin;
			}
			//�ڶ���Ҫ���ѣ�Ĭ�Ͻ����Ǵ��--�������µ����㷨����
			//�����һ��Ҷ�ӽ��ĸ��׿�ʼ���µ���
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
			//�����װ��������ֱ��������ɾ�����һ������
			_con.pop_back();

			Adjustdown(0);
		}
		void push(const T& val)
		{
			_con.push_back(val);
			//ʹ�����ϵ����㷨��������
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
		//��������������װ��һ������,�����ȼ����в�ֻ�Ǽ򵥵�������װ��������������ݽ����˼ӹ������뾡�������ݻ�Ҫ�����㷨���е���
	};
	//�º���/��������
	template<class T>
	class Less
	{
	public:
		
		bool operator()( T& x, T& y)//����()  Ҳ��һ�ַ��ͣ� �Կ��ƱȽϵķ���
		{
			return x < y;
		}
	};
	template<class T>
	class Greater
	{
	public:
		
		bool operator()( T& x,  T& y)//����()  Ҳ��һ�ַ��ͣ� �Կ��ƱȽϵķ���
		{
			return x > y;
		}
	};
	class LessPData
	{
	public:

		bool operator()( Data* d1, const Data* d2)//����()  Ҳ��һ�ַ��ͣ� �Կ��ƱȽϵķ���
		{
			return  *d1<*d2;
		}
	};
};