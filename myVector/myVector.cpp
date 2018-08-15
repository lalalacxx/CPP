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

	T& Back()
	{
		return *(_finish-1);
	}

	T& Front()
	{
		return *(_first);
	}
private:
    T *_start;
    T *_end;
    T *_endofstorage;
};
