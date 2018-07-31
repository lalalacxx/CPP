#include <iostream>
using namespace std;

class Date
{
public:
    //判断是否为闰年
    
    //获取每个月的天数
    int GetMonthDay(int year,int month)
    {
        int days[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        if(month == 2 && IsLeap(year))
        {
            ++days[2];
        }
        return days[month];
    }
    //判断日期是否合法
    bool IsInvalid()
    {
        return _year>=1900 
            && (_month>=1 && _month<=12)
            && (_day>=1 && _day<=GetMonthDay(_year,_month));
    }
    //构造函数
    Date(int year,int month,int day)
        :_year(year)
         ,_month(month)
         ,_day(day)
    {
        if(!IsInvalid())
        {
            assert(false);
        }
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
