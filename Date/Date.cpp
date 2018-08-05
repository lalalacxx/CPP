#include <iostream>
#include<assert.h>
#include<stdio.h>
using namespace std;

class Date
{
public:
    void show()
    {
        cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
    }
    //判断是否为闰年
    bool IsLeap(int year)
    {
        if((year%4 == 0 && year%100!=0)
           || year%400 == 0)
            return true;
        else
            return false;
    }
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
    Date(int year=1900,int month=1,int day=1)
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
        _year = d._year;
        _month = d._month;
        _day = d._day;
    }
    //析构函数,这里并没有什么好清理的，因此无需自定义一个析构函数
    //~Date(){};
    //赋值运算符重载
    Date& operator=(const Date& d)
    {
        if(*this != d)//避免自己给自己赋值
        {
            _year = d._year;
            _month = d._month;
            _day = d._day;
        }
        return *this;
    }
    //==运算符的重载
    bool operator==(const Date& d)
    {
        if(_year == d._year && _month == d._month && _day == d._day)
        {
            return true;
        }
        return false;
    }
    //!=运算符的重载
    bool operator!=(const Date& d)
    {
        return !(*this==d);
    }
    //>运算符的重载
    bool operator>(const Date& d)
    {
        if(_year == d._year)
        {
            if(_month == d._month)
            {
                if(_day > d._day)
                {
                    return true;
                }
            }
            else if(_month > d._month)
            {
                return true;
            }
        }
        else if(_year > d._year)
        {
            return true;
        }
        return false;
    }
    //<运算符的重载
    bool operator<(const Date& d)
    {
        return !(*this>d) && !(*this==d);
    }
    //>=运算符的重载
    bool operator>=(const Date& d)
    {
        return !(*this<d);
    }
    //<=运算符的重载
    bool operator<=(const Date& d)
    {
        return !(*this>d);
    }
    //+=运算符的重载
    Date& operator+=(int day)
    {
        _day+=day;
        //先判断天数是否合法
        while(_day > GetMonthDay(_year,_month))
        {
            //天数不合法，则先减去当月的天数
            _day -= GetMonthDay(_year,_month);
            //并让月份+1
            _month += 1;
            //接着判断月份是否合法
            if(_month > 12)
            {
                //不合法则让年份+1
                _year += 1;
                //并且月份从头开始
                _month = 1;
            }
            //一直循环直到天数合法为止
        }
        return *this;
    }
    //+运算符重载
    Date operator+(int day)
    {
        Date ret(*this);
        ret += day;
        return ret;
    }
    //-=运算符重载
    Date& operator-=(int day)
    {
        while(_day < day)
        {
            //如果要剪掉的天数大于当前的日期（天）
            //则借上一个月的天数
            _month -= 1;//即把月份-1
            if(_month == 0)
            {
                //判断月份不合法，则向上一个年份借一个月
                _year -= 1;//即把年份-1
                _month = 12;//月份置为12
            }
            //把借的天数与当前的天数相加
            //直到天数满足要减去的天数退出循环
            _day += GetMonthDay(_year,_month);
        }
        _day-=day;
        return *this;
    }
    //-运算符重载
    Date operator-(int day)
    {
        Date ret(*this);
        ret -= day;
        return ret;
    }
    //两个日期的相减
    int operator-(const Date& d)
    {
        Date max(*this);
        Date min(d);
        int flag = 1;//大日期-小日期，结果为正数
        if(*this < d)
        {
            max = d;
            min = *this;
            flag = -1;//小日期-大日期，结果为负数
        }
        int count = 0;
        while(max != min)
        {
            //将日期较小的这一个，一天一天的往上加，
            //直到与较大的日期相等，那么加了多少次，
            //就说明之间相差多少天
            min++;
            count++;
        }
        return flag*count;
    }
    //前置++运算符的重载
    Date& operator++()
    {
        *this += 1;
        return *this;
    }
    //后置++运算符的重载
    Date operator++(int)
    {
        Date ret(*this);
        *this += 1;
        return ret;
    }
    //前置--运算符的重载
    Date& operator--()
    {
        *this -= 1;
        return *this;
    }
    //后置--运算符的重载
    Date operator--(int)
    {
        Date ret(*this);
        *this -= 1;
        return ret;
    }
    
private:
    int _year;
    int _month;
    int _day;
};
void test()
{
    //构造函数测试
    Date d1(2018,1,1);
    d1.show();    
    //拷贝构造函数测试
    Date d2(d1);
    d2.show();
    //赋值运算符重载函数测试
    Date d3;
    d3 = d1;
    d3.show();
    //==运算符重载函数测试
    if(d1==d2)
    {
        printf("d1与d2相等\n");
    }
    //>运算符重载函数测试
    ++d3;
    if(d3>d1)
    {
        printf("d3大于d1\n");
    }
    //+=运算符重载函数测试
    Date d4 = d3+=3;
    d4.show();
    //-=运算符重载函数测试
    Date d5 = d3-=4;
    d5.show();    
}
int main()
{
    test();
    return 0;
}
