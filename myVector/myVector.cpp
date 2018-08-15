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
		//Insert(0, x);
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

	void PopBack()
	{
		Erase(Size()-1);
	}

	void Insert(size_t pos, const T& x)
	{
		assert(pos <= Size());

		if (_finish == _endofstorage)
		{
			size_t newcapacity = Capacity() == 0 ? 3 : Capacity()*2;
			Expand(newcapacity);
		}

		T* end = _finish-1;
		while (end >= _first+pos)
		{
			*(end+1) = *end;
			--end;
		}

		//*(_first+pos) = x;
		_first[pos] = x;
		++_finish;
	}	

	void Erase(size_t pos)
	{
		assert(pos < Size());

		T* start = _first + pos;
		while (start < _finish-1)
		{
			*start = *(start+1);
			++start;
		}

		--_finish;
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
