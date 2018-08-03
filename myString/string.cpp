#include<iostream>
#include<string.h>
#include<assert.h>
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
    void Resize(size_t n)
    {

    }
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
            size_t newcapacity = _capacity*2;
            while(newcapacity< _size+len)
            {
                newcapacity *= 2;
            }
            Expand(_size+len);
        }
        strcpy(_str+_size,str);
        _size += len;
        Insert(_size,str);
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
private:
    char *_str;
    size_t _size;
    size_t _capacity;
};
