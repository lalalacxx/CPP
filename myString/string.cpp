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
    size_t Size()
    {
        return _size;
    }
    size_t Capacity()
    {
        return _capacity;
    }
    char *Str()
    {
        return _str;
    }
    bool Empty()
    {
        return _size == 0;
    }
    char& operator[](size_t pos)
    {
        return _str[pos];
    }
    
    void Reserve(size_t n)
    {
        Expand(n);
    }
    //可能会同时改变size和capacity
    //还会进行初始化(缺省初始化为\0)
    void Resize(size_t n,char ch = '\0')
    {
        if(n < _size)
        {
            _str[n] = '\0';
            _size = n;
        }
        else
        {
            if(n > _capacity)
            {
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
    //扩容
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
    void PushBack(char ch)
    {
       // if(_size == _capacity)
       // {
       //     Expand(_capacity*2);
       // }
       // _str[_size] = ch;
       // _str[_size+1] = '\0';
       // ++_size;
        Insert(_size,ch);
    }
    void Append(const char *str)
    {
        size_t len = strlen(str);
        if(_size+len >_capacity)
        {
           // size_t newcapacity = _capacity*2;
           // while(newcapacity< _size+len)
           // {
           //     newcapacity *= 2;
           // }
            Expand(_size+len);
        }
        strcpy(_str+_size,str);
        _size += len;
        //Insert(_size,str);
    }
    //某个位置插入字符
    void Insert(size_t pos,char ch)
    {
        assert(pos <= _size);
        if(_capacity == _size)
        {
            Expand(_capacity*2);
        }
        int end = _size;
        while(end >= (int)pos)
        {
            _str[end+1] = _str[end];
            --end;
        }
        _str[pos] = ch;
        ++_size;
    }
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
    }
    //s1+="hello"
    String& operator+=(const char *str)
    {
        this->Append(str);
        return *this;
    }
    //s1+=s2
    String operator+=(const String& s)
    {
        *this += s._str;//this->operator+=(this,s._str);
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
    void PopBack()
    {
        assert(_size > 0);
        --_size;
        _str[_size] = '\0';
    }
    void Erase(size_t pos,size_t len)
    {
        assert(pos < _size);
        if(pos+len >= _size)
        {
            _str[pos] = '\0';
            _size = pos;
        }
        else
        {
            size_t start = pos+len;
            _str[pos] = _str[start];
            strcpy(_str+pos,_str+pos+len);
            _size -= len;
        }
    }
    size_t Find(char ch)
    {
        for(size_t i = 0;i < _size;i++)
        {
            if(_str[i] == ch)
            {
                return i;
            }
        }
        return npos;
    }
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
    s.Erase(1,1);
    std::cout<<s.Str()<<std::endl;
    s.Erase(5,10);
    std::cout<<s.Str()<<std::endl;
    //Find函数测试
    size_t ret = s.Find('a');
    size_t ret1 = s.Find('h');
    if(ret1 != String::npos)
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
