#include<iostream>
#include<string.h>
#include<assert.h>
#include<stdio.h>

class String
{
public:
    //构造函数
    String(const char *str="")
        :_size(strlen(str))
        ,_capacity(_size)
    {
        _str = new char[_size+1];
        strcpy(_str,str);
    }
    void Swap(String& s)
    {
        std::swap(_str,s._str);
        std::swap(_size,s._size);
        std::swap(_capacity,s._capacity);
    }
    //拷贝构造
    String(const String& s)
        :_str(NULL)
    {
        String tmp(s._str);
        this->Swap(tmp);
    }
    //赋值运算符的重载
    String& operator=(String s)
    {
        this->Swap(s);
        return *this;
    }
    //析构函数
    ~String()
    {
        if(_str)
        {
            delete[] _str;
            _str = NULL;
        }
    }
    //求string的字符个数
    size_t Size()
    {
        return _size;
    }
    //求string的容量
    size_t Capacity()
    {
        return _capacity;
    }
    //求string的内容
    char *Str()
    {
        return _str;
    }
    //判断string是否为空
    bool Empty()
    {
        return _size == 0;
    }
    //[]操作符的重载
    char& operator[](size_t pos)
    {
        return _str[pos];
    }
    //扩容，只会改变_capacity的大小
    void Reserve(size_t n)
    {
        Expand(n);
    }
    //可能会同时改变_size和_capacity
    //并且还会进行初始化(缺省初始化为'\0')
    void Resize(size_t n,char ch = '\0')
    {
        if(n <= _size)
        {
	        //此时因为是缩小了或者不变所以不用改变_capacity的值
            _str[n] = '\0';
            _size = n;
        }
        else
        {
            if(n > _capacity)
            {
	            //此时n超过了容量的大小因此需要扩容
                Expand(n);
            }
            for(size_t i = _size;i < n;++i)
            {
                _str[i] = ch;
            }
            _str[n] = '\0';
            _size = n;
        }
    }
    //扩容函数（这里涉及到一个问题就是如何扩容？？附在代码后面）
    void Expand(size_t n)
    {
        if(n > _capacity)
        {
            char *tmp = new char[n+1];
            strcpy(tmp,_str);
            delete[] _str;
            _str = tmp;
            _capacity = n;
        }
    }
    //尾插函数
    void PushBack(char ch)
    {
	    //方法1：
       // if(_size == _capacity)
       // {
       //     Expand(_capacity*2);
       // }
       // _str[_size] = ch;
       // _str[_size+1] = '\0';
       // ++_size;
        //方法2：可直接调用实现的Insert()函数
        Insert(_size,ch);
    }
    //在string的后面追加一个字符串
    void Append(const char *str)
    {
        size_t len = strlen(str);
        if(_size+len >_capacity)
        {
            Expand(_size+len);
        }
        strcpy(_str+_size,str);//接着_str的末尾开始往后拷贝
        _size += len;
    }
    //某个位置插入字符
    void Insert(size_t pos,char ch)
    {
        assert(pos <= _size);
        if(_capacity == _size)
        {
	        //此时已经相等，如果在想插入一个元素则空间肯定不够，
	        //需要扩容
            Expand(_capacity*2);
        }
        int end = _size;
        while(end >= (int)pos)
        {
	        //把包括pos位置在内的往后所有元素依次往后移动一个位置
            _str[end+1] = _str[end];
            --end;
        }
        //移动完成以后，pos位置就空出来了，将待插入的元素插入
        _str[pos] = ch;
        ++_size;
    }
    //某个位置插入字符串
    void Insert(size_t pos,const char *str)
    {
        assert(pos <= _size);
        size_t len = strlen(str);
        if(_size + len > _capacity)
        {
            Expand(_size+len);
        }
        int end = _size;
        while(end >= (int)pos)
        {
            _str[end+len] = _str[end];
            --end;
        }
        strncpy(_str+pos,str,len);
        //使用strncpy不会将待插入的字符串的'\0'也拷贝进目标字符串
    }
    //s1+="hello" +=运算符重载，与Append函数功能相同
    String& operator+=(const char *str)
    {
        this->Append(str);
        return *this;
    }
    //s1+=s2 两个string类的+=实现
    String operator+=(const String& s)
    {
        *this += s._str;//相当于this->operator+=(this,s._str);
        return *this;
    }
    //s1+"hello"
    String operator+(const char *str)
    {
        String ret(*this);
        ret.Append(str);
        return ret;
    }
    //s1+s2
    String operator+(const String s)
    {
        return *this+s._str;
    }
    //尾删
    void PopBack()
    {
        assert(_size > 0);
        --_size;
        _str[_size] = '\0';
    }
    //删除某一位置往后的len个元素
    void Erase(size_t pos,size_t len)
    {
        assert(pos < _size);
        if(pos+len >= _size)
        {
	        //此种情况就是将pos往后的所有都删掉
            _str[pos] = '\0';
            _size = pos;
        }
        else
        {
            strcpy(_str+pos,_str+pos+len);
            _size -= len;
        }
    }
    //在string中查找是否存在某一个字符，若存在返回下标
    size_t Find(char ch)
    {
        for(size_t i = 0;i < _size;i++)
        {
            if(_str[i] == ch)
            {
                return i;
            }
        }
        //这里的npos是string类中的一个公有的成员变量（值为-1）
        //返回这个就说明没有找到
        return npos;
    }
    //在string中查找是否存在某一个子串，类似于strstr函数
    size_t Find(const char *sub) const
    {
        if(sub == NULL)
        {
            return npos;
        }
        char *ret = _str;
        while(*ret)
        {
            char *cur_tmp = (char *)sub;
            char *str_tmp = ret;
            while(*str_tmp && cur_tmp && *str_tmp == *cur_tmp)
            {
                str_tmp++;
                cur_tmp++;
            }
            if(*cur_tmp == '\0')
            {
	            //找到了，返回匹配到的子串往后的字符串
	            //如查找abc在dabcjd23dabce中是否存在，
	            //结果返回abcjd23dabce这个字符串
                return ret-_str;
            }
            else
            {
                ret++;
            }
        }
        return npos;
    }
    bool operator<(const String& s) const
    {
        const char* str1 = _str;
        const char* str2 = s._str;
        while(*str1 && *str2)
        {
            if(*str1 < *str2)
                return true;
            else if(*str1 > *str2)
                return false;
            else
            {
                ++str1;
                ++str2;
            }
        }
        if(*str1 == '\0' && *str2 != '\0')
        {
	        //str1字符串比str2这个字符串要短
            return true;
        }
        else
        {
            return false;
        }
    }
    bool operator<=(const String& s) const
    {
        return *this<s || *this==s;
    }
    bool operator>(const String& s) const
    {
        return !(*this<=s);
    }
    bool operator>=(const String& s) const
    {
        return !(*this<s);
    }
    bool operator==(const String& s) const
    {
        const char *str1 = _str;
        const char *str2 = s._str;
        while(*str1 && *str2)
        {

            if(*str1 != *str2)
            {
                return false;
            }
            else
            {
                ++str1;
                ++str2;
            }
        }
        if(*str1 == '\0' && *str2 == '\0')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool operator!=(const String& s) const
    {
        return !(*this==s);
    }
private:
    char *_str;
    size_t _size;
    size_t _capacity;
public:
    static size_t npos;
};
size_t String::npos = -1;


void Test()
{
    String s("hello");
    //拷贝构造函数测试
    String s1(s);
    std::cout<<s1.Str()<<std::endl;
    //赋值运算符重载函数测试
    String s2;
    s2 = s;
    std::cout<<s2.Str()<<std::endl;
    //[]运算符重载函数测试
    std::cout<<s[0]<<std::endl;
    //PushBack函数测试
    s.PushBack(' ');
    std::cout<<s.Str()<<std::endl;
    //Append函数测试
    s.Append("world");
    std::cout<<s.Str()<<std::endl;
    //Insert函数测试
    s.Insert(11,'O');
    std::cout<<s.Str()<<std::endl;
    s.Insert(1,'H');
    std::cout<<s.Str()<<std::endl;
    //s.Insert(15,'&');
    //std::cout<<s.Str()<<std::endl;
    //PopBack函数测试
    s.PopBack();
    std::cout<<s.Str()<<std::endl;
    //Erase函数测试
    s.Erase(2,3);
    std::cout<<s.Str()<<std::endl;
    s.Erase(5,10);
    std::cout<<s.Str()<<std::endl;
    //Find函数测试
    size_t ret = s.Find('a');
    //size_t ret = s.Find('h');
    if(ret != String::npos)
    {
        printf("找到了\n");
    }
    else
    {
        printf("没找到\n");
    }
}
int main()
{
    Test();
    return 0;
}
