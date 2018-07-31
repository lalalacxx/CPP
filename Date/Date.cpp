#include <iostream>
using namespace std;

class Date
{
public:
    //判断日期是否合法
    bool IsInvalid(int year,int month,int day)
    {
        if(year >= 1900 && (month >= 1 && month <= 12) && day)
    }
    //构造函数
    Date(int year,int month,int day)
    {

    }
    //拷贝构造函数
    Date(const Date& d)
    {

    }
    //析构函数
    ~Date()
    {

    }
    //赋值运算符重载
    //
    //
    //
    //
    //
private:
    int _year;
    int _month;
    int _day;
};
