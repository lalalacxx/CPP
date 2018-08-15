#include <iostream>
template<typename T>
class Vector
{
public:
    //构造函数
    Vector()
        :_start(NULL)
         ,_end(NULL)
         ,_endofstorage(NULL)
    {}
    //拷贝构造函数
    Vector(const Vector<T>& v)
    {
        _start = new T[v.Size()];
		for (size_t i = 0; i < v.Size(); ++i)
		{
			_start[i] = v._start[i]; // operator=
		}

		_end =  _start + v.Size();
		_endofstorage = _start + v.Size();

    }
    //析构函数
	~Vector()
	{
		if (_start)
		{
			delete[] _start;
		}
		_start = _end = _endofstorage = NULL;
	}
    //赋值操作符重载
	Vector<T>& operator=(Vector<T> v)
	{
		swap(_start, v._start);
		swap(_end, v._end);
		swap(_endofstorage, v._endofstorage);
		return *this;
	}
    //取最后一个元素
	T& Back()
	{
		return *(_end-1);
	}
    //取第一个元素
	T& Front()
	{
		return *(_start);
	}
    //尾插
	void PushBack(const T& x)
	{
		if (_end == _endofstorage)
		{
			size_t newcapacity = Capacity() == 0 ? 3 : Capacity()*2;
			Expand(newcapacity);
		}
        //扩容完成以后将元素插入
		*_end = x;
        //最终将_end的位置更新
		++_end;
	}
    //尾删
	void PopBack()
	{
        //调用Erase函数辅助完成
		Erase(Size()-1);
	}
    //任意位置插入一个元素函数
	void Insert(size_t pos, const T& x)
	{
        //pos位置的合法性检测
		assert(pos <= Size());

		if (_end == _endofstorage)
		{
			size_t newcapacity = Capacity() == 0 ? 3 : Capacity()*2;
			Expand(newcapacity);
		}
		T* finish = _end-1;
        //这种情况是待插入的位置在原有元素区间
        //[_start,_end)之内
		while (finish >= _start+pos)
		{
            //循环的将pos（包括pos位置在内）
            //之后的元素往后移动一位
			*(finish+1) = *finish;
			--finish;
		}
        //将待插入的元素赋值给pos位置
		_start[pos] = x;
		++_end;
	}	
    //任意位置元素删除
	void Erase(size_t pos)
	{
        //pos位置的合法性检测
		assert(pos < Size());

		T* tmp = _start + pos;
		while (tmp < _end-1)
		{
            //直接将pos位置往后的所有元素
            //往前移动一位，将pos位置覆盖即可
			*tmp = *(tmp+1);
			++tmp;
		}
		--_end;
	}

	size_t Size() const
	{
		return _finish - _first;
	}

	size_t Capacity() const
	{
		return _endofstorage - _first;
	}

	bool Empty()
	{
		return _first == _finish;
	}

	T& operator[](size_t pos)
	{
		assert(pos < Size());

		return _first[pos];
	}
private:
    T *_start;
    T *_end;
    T *_endofstorage;
};
