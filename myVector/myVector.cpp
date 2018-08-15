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
private:
    T *_start;
    T *_end;
    T *_endofstorage;
};
