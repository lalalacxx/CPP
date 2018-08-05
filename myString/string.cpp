#include<iostream>
#include<string.h>
#include<assert.h>
#include<stdio.h>

class String
{
public:
    //���캯��
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
    //��������
    String(const String& s)
        :_str(NULL)
    {
        String tmp(s._str);
        this->Swap(tmp);
    }
    //��ֵ�����������
    String& operator=(String s)
    {
        this->Swap(s);
        return *this;
    }
    //��������
    ~String()
    {
        if(_str)
        {
            delete[] _str;
            _str = NULL;
        }
    }
    //��string���ַ�����
    size_t Size()
    {
        return _size;
    }
    //��string������
    size_t Capacity()
    {
        return _capacity;
    }
    //��string������
    char *Str()
    {
        return _str;
    }
    //�ж�string�Ƿ�Ϊ��
    bool Empty()
    {
        return _size == 0;
    }
    //[]������������
    char& operator[](size_t pos)
    {
        return _str[pos];
    }
    //���ݣ�ֻ��ı�_capacity�Ĵ�С
    void Reserve(size_t n)
    {
        Expand(n);
    }
    //���ܻ�ͬʱ�ı�_size��_capacity
    //���һ�����г�ʼ��(ȱʡ��ʼ��Ϊ'\0')
    void Resize(size_t n,char ch = '\0')
    {
        if(n <= _size)
        {
	        //��ʱ��Ϊ����С�˻��߲������Բ��øı�_capacity��ֵ
            _str[n] = '\0';
            _size = n;
        }
        else
        {
            if(n > _capacity)
            {
	            //��ʱn�����������Ĵ�С�����Ҫ����
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
    //���ݺ����������漰��һ���������������ݣ������ڴ�����棩
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
    //β�庯��
    void PushBack(char ch)
    {
	    //����1��
       // if(_size == _capacity)
       // {
       //     Expand(_capacity*2);
       // }
       // _str[_size] = ch;
       // _str[_size+1] = '\0';
       // ++_size;
        //����2����ֱ�ӵ���ʵ�ֵ�Insert()����
        Insert(_size,ch);
    }
    //��string�ĺ���׷��һ���ַ���
    void Append(const char *str)
    {
        size_t len = strlen(str);
        if(_size+len >_capacity)
        {
            Expand(_size+len);
        }
        strcpy(_str+_size,str);//����_str��ĩβ��ʼ���󿽱�
        _size += len;
    }
    //ĳ��λ�ò����ַ�
    void Insert(size_t pos,char ch)
    {
        assert(pos <= _size);
        if(_capacity == _size)
        {
	        //��ʱ�Ѿ���ȣ�����������һ��Ԫ����ռ�϶�������
	        //��Ҫ����
            Expand(_capacity*2);
        }
        int end = _size;
        while(end >= (int)pos)
        {
	        //�Ѱ���posλ�����ڵ���������Ԫ�����������ƶ�һ��λ��
            _str[end+1] = _str[end];
            --end;
        }
        //�ƶ�����Ժ�posλ�þͿճ����ˣ����������Ԫ�ز���
        _str[pos] = ch;
        ++_size;
    }
    //ĳ��λ�ò����ַ���
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
        //ʹ��strncpy���Ὣ��������ַ�����'\0'Ҳ������Ŀ���ַ���
    }
    //s1+="hello" +=��������أ���Append����������ͬ
    String& operator+=(const char *str)
    {
        this->Append(str);
        return *this;
    }
    //s1+=s2 ����string���+=ʵ��
    String operator+=(const String& s)
    {
        *this += s._str;//�൱��this->operator+=(this,s._str);
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
    //βɾ
    void PopBack()
    {
        assert(_size > 0);
        --_size;
        _str[_size] = '\0';
    }
    //ɾ��ĳһλ�������len��Ԫ��
    void Erase(size_t pos,size_t len)
    {
        assert(pos < _size);
        if(pos+len >= _size)
        {
	        //����������ǽ�pos��������ж�ɾ��
            _str[pos] = '\0';
            _size = pos;
        }
        else
        {
            strcpy(_str+pos,_str+pos+len);
            _size -= len;
        }
    }
    //��string�в����Ƿ����ĳһ���ַ��������ڷ����±�
    size_t Find(char ch)
    {
        for(size_t i = 0;i < _size;i++)
        {
            if(_str[i] == ch)
            {
                return i;
            }
        }
        //�����npos��string���е�һ�����еĳ�Ա������ֵΪ-1��
        //���������˵��û���ҵ�
        return npos;
    }
    //��string�в����Ƿ����ĳһ���Ӵ���������strstr����
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
	            //�ҵ��ˣ�����ƥ�䵽���Ӵ�������ַ���
	            //�����abc��dabcjd23dabce���Ƿ���ڣ�
	            //�������abcjd23dabce����ַ���
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
	        //str1�ַ�����str2����ַ���Ҫ��
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
    //�������캯������
    String s1(s);
    std::cout<<s1.Str()<<std::endl;
    //��ֵ��������غ�������
    String s2;
    s2 = s;
    std::cout<<s2.Str()<<std::endl;
    //[]��������غ�������
    std::cout<<s[0]<<std::endl;
    //PushBack��������
    s.PushBack(' ');
    std::cout<<s.Str()<<std::endl;
    //Append��������
    s.Append("world");
    std::cout<<s.Str()<<std::endl;
    //Insert��������
    s.Insert(11,'O');
    std::cout<<s.Str()<<std::endl;
    s.Insert(1,'H');
    std::cout<<s.Str()<<std::endl;
    //s.Insert(15,'&');
    //std::cout<<s.Str()<<std::endl;
    //PopBack��������
    s.PopBack();
    std::cout<<s.Str()<<std::endl;
    //Erase��������
    s.Erase(2,3);
    std::cout<<s.Str()<<std::endl;
    s.Erase(5,10);
    std::cout<<s.Str()<<std::endl;
    //Find��������
    size_t ret = s.Find('a');
    //size_t ret = s.Find('h');
    if(ret != String::npos)
    {
        printf("�ҵ���\n");
    }
    else
    {
        printf("û�ҵ�\n");
    }
}
int main()
{
    Test();
    return 0;
}
