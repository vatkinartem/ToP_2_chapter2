#pragma once
#include "MyExceptions.h"
#include <math.h>

#ifndef MYVECTOR_H
#define MYVECTOR_H



namespace myvec {
/*My vector container with lesser functionality and optimisation*/
template <class Type>
class MyVector
{
public:
	friend void swap(MyVector<Type>& _dest, MyVector<Type>& _source) noexcept;

	MyVector();
	MyVector(const MyVector<Type>& _myVector);
	MyVector(MyVector<Type>&& _myVector) noexcept;
	virtual ~MyVector();
	std::string getClassName() const;
	Type** getData() const;
	Type** getFront() const;
	Type** getBack() const;

	void pushBack(const Type& value);
	void pushBack(const MyVector<Type>& _source);
	void pushBack(Type&& value) noexcept;
	void pushBack(MyVector<Type>&& _source) noexcept;
	void popBack();
	void emplace(long long index, const Type& value);
	void emplace(long long index, Type&& value);

	MyVector<Type>& reserve(long long _capacity);				/*allocating memory for new pointers for elements*/
	MyVector<Type>& resize(long long _size);					/*changing size of used area and if needed calling reserve()*/
	MyVector<Type>& shrink_to_fit();
	MyVector<Type> getRange(long long _from, long long _to);
	MyVector<Type>& erase(long long _index);
	MyVector<Type>& erase(long long _from, long long _to);
	bool empty() const;
	bool isFree() const;
	MyVector<Type>& clear();
	MyVector<Type>& freeMyVector();

	long long getSize() const;
	long long getCapacity() const;

	const Type& operator[] (long long _index) const;
	Type& operator[] (long long _index);

	MyVector<Type>& operator= (const MyVector<Type>& _myVector);
	MyVector<Type>& operator= (MyVector<Type>&& _myVector) noexcept;

	MyVector<Type>& operator+ (const MyVector<Type>& _myVector);
	MyVector<Type>& operator+ (MyVector<Type>&& _myVector) noexcept;

protected:
	
private:
	Type** data;					/*Poiner on data of vector*/
	Type** front;				/*Pointer on first element in used block*/
	Type** back;					/*Pointer on last element in used block*/
	long long size;			/*Number of Type elements in vector*/
	long long capacity;		/*Number of allocated Type elements in vector*/

	/*destroying element if it is not trivially destructable*/
	void destroy_in_place(Type& _obj);
	/*destroying range of elements*/
	void destroy_range(Type& _first, Type& _last);
	/*Just nullifying all values of MyVector obj. (Including pointers, so be sure to free them first or you will have to deal with memory leak)*/
	void nullifyParams();
	/*Allocating new block of memory (and returning adress in data) and copying elements from the source*/
	void copyData(const MyVector<Type>& _myVector);
	virtual long long calcNewCapacity(long long num);
	
};



}	// myvec






//Implementation------------------------------------------------MyVector.cpp-----------------------------------------------------

#pragma once
#include <iostream>
#include <malloc.h>
#include <string>


#ifndef MYVECTOR_CPP
#define MYVECTOR_CPP

using std::string;
using std::exception;

namespace myvec {

#define MAX_ALLOC_TIMES 10
#define MAX_SIZE INT32_MAX
constexpr auto RESERVE_STEP = 1;	/*the higher the value the less aloocations will be (so it will be faster) but less memory efficient*/


/*Default Constructor*/
template<class Type>
inline MyVector<Type>::MyVector()
{
	this->nullifyParams();
}

/*Conctructor of Copying*/
template<class Type>
inline MyVector<Type>::MyVector(const MyVector<Type>& _myVector)
{
	this->nullifyParams();
	this->copyData(_myVector);
}

/*Conctructor of Transporting*/
template<class Type>
inline MyVector<Type>::MyVector(MyVector<Type>&& _myVector) noexcept
{
	this->data = _myVector.data;
	this->front = _myVector.front;
	this->back = _myVector.back;
	this->size = _myVector.size;
	this->capacity = _myVector.capacity;
	_myVector.nullifyParams();
}

/*Destructor*/
template<class Type>
MyVector<Type>::~MyVector()
{
	this->freeMyVector();
}

template<class Type>
inline std::string MyVector<Type>::getClassName() const
{
	return string("MyVector<Type>");
}

template<class Type>
inline Type** MyVector<Type>::getData() const
{
	return this->data;
}

template<class Type>
inline Type** MyVector<Type>::getFront() const
{
	return this->front;
}

template<class Type>
inline Type** MyVector<Type>::getBack() const
{
	return this->back;
}

template<class Type>
inline void MyVector<Type>::pushBack(const Type& value)
{
	if ((this->size + 1) > this->capacity)	/*if future size is larger then cur capacity then reserve RESERVE_STEP more elements (by defalt it is 1)*/
	{
		this->reserve(calcNewCapacity( this->capacity + 1 ));		/*it could be resize() but I wanted to optimize it little*/
	}
	/* this->back now has to be pointing at newly allocated element*/
	
	try
	{
		this->front[this->size] = new Type;
		if (this->front[this->size] == nullptr)
		{
			throw MyException("Couldnt allocate memory in pushBack(const MyVector<Type>& _source) func.") ;
		}
		*this->front[this->size] = value;
		this->size++;
		this->back++;
	}
	catch (const exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

template<class Type>
inline void MyVector<Type>::pushBack(const MyVector<Type>& _source)
{
	/*if source is empty then just skipping*/
	if (_source.empty())
	{
		return;
	}
	/*if future size is larger then cur capacity then reserving for extra elements*/
	if ((this->size + _source.size) > this->capacity)
	{
		this->reserve(calcNewCapacity(this->size + _source.size));
	}

	/*adding elems to back from source*/
	for (long long i = 0; i < _source.size; i++)
	{
		this->pushBack(_source[i]);
	}
}

template<class Type>
inline void MyVector<Type>::pushBack(Type&& value) noexcept
{
	if ((this->size + 1) > this->capacity)	/*if future size is larger then cur capacity then reserve RESERVE_STEP more elements (by defalt it is 1)*/
	{
		this->reserve(calcNewCapacity(this->capacity + 1));		/*it could be resize() but I wanted to optimize it little*/
	}
	/* this->back now has to be pointing at newly allocated element*/

	try
	{
		this->front[this->size] = new Type;
		if (this->front[this->size] == nullptr)
		{
			throw MyException("Couldnt allocate memory in pushBack(const MyVector<Type>& _source) func.") ;
		}
		*this->front[this->size] = std::move(value);
		this->size++;
		this->back++;
	}
	catch (const exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

template<class Type>
inline void MyVector<Type>::pushBack(MyVector<Type>&& _source) noexcept
{
	/*if source is empty then just skipping*/
	if (_source.empty())
	{
		return;
	}
	/*if future size is larger then cur capacity then reserving for extra elements*/
	if ((this->size + _source.size) > this->capacity)
	{
		this->reserve(calcNewCapacity(this->size + _source.size));
	}

	/*adding elems to back from source*/
	for (long long i = 0; i < _source.size; i++)
	{
		this->pushBack(std::move(_source[i]));
	}

	_source.nullifyParams();
}

template<class Type>
inline void MyVector<Type>::popBack()
{
	if (this->front == this->back)
	{
		/*Because nothing to erase*/
	}
	else if ((this->size - 1) > 0)	/*erasing last element*/
	{
		this->erase(this->size - 1);
	}
}

template<class Type>
inline void MyVector<Type>::emplace(long long index, const Type& value)
{
	if (this->front == this->back)
	{
		throw MyException("Vector is empty. Cant reach this index.") ;
	}
	if ((index < 0) || (index > (this->size - 1)))
	{
		throw MyException("Index is out of range. Cant reach this index.") ;
	}
	this->erase(index);
	this->front[index] = new Type;
	*this->front[index] = value;
}

template<class Type>
inline void MyVector<Type>::emplace(long long index, Type&& value)
{
	if (this->front == this->back)
	{
		throw MyException("Vector is empty. Cant reach this index." );
	}
	if ((index < 0) || (index > (this->size - 1)))
	{
		throw MyException("Index is out of range. Cant reach this index.") ;
	}
	*this->front[index] = std::move(value);
}

template<class Type>
void swap(MyVector<Type>& _dest, MyVector<Type>& _source) noexcept
{
	MyVector<Type> temp = std::move(_dest);
	_dest = std::move(_source);
	_source = std::move(temp);
	temp.nullifyParams();
}

/*Allocating memory with _capacity of Type elements*/
template<class Type>
inline MyVector<Type>& MyVector<Type>::reserve(long long _capacity)
{
	Type** temp_ptr = nullptr;
	long long newSize = 0;
	/*If we need to make a vector with zero than we want to free it, so we are doing it in if statment below*/
	if (_capacity == 0)
	{
		if (this->capacity != 0)
		{
			this->freeMyVector();
		}
		return *this;
	}

	if (_capacity < 0)
	{
		std::cout << "Cant allocate vector. Size is less than zero." << std::endl;
		return *this;
	}
	if (_capacity >= MAX_SIZE)
	{
		std::cout << "Cant allocate vector. Size is TOO big." << std::endl;
		return *this;
	}

	/*if we have free vector then just allocating needed amount of memory*/
	if (this->data == nullptr)
	{
		try
		{
			temp_ptr = new Type* [_capacity];
			if (temp_ptr == nullptr)
			{
				throw MyException("Couldnt allocate memory in reserve(long long _capacity) func. If free statment.") ;
			}
		}
		catch (const exception& ex)
		{
			std::cout << ex.what() << std::endl;
			return *this;
		}
		this->data = temp_ptr;
		this->capacity = _capacity;
		this->front = this->data;
		this->back = this->data;
		return *this;
	}
	else
	{
		/*else we have to transport used data from old vec to new
		(it actually does not matter if is it empty vec or not, so I also did it in universal way, so it is not as optimized as it could be)*/
		newSize = this->size;
		if (this->size > _capacity)	/*if size will get smaller after reserve then we have to destroy useless elements*/
		{
			newSize = _capacity;
			erase(newSize, this->size - 1);		/* erasing useless*/
		}
			/*reallocating vec with capacity of prev vec*/
		try
		{
			temp_ptr = (Type**)realloc(this->data, _capacity * sizeof(Type*));
			if (temp_ptr == nullptr)
			{
				throw MyException("Couldnt reallocate poiner data in reserve(long long _capacity) func. Else transporting statment.") ;
			}
		}
		catch (const exception& ex)
		{
			std::cout << ex.what() << std::endl;
			return *this;
		}

		this->data = temp_ptr;
		this->capacity = _capacity;
		this->size = newSize;									/*predetermine future size*/
		this->front = this->data;
		this->back = this->data + this->size;		 			/*predetermine future back ptr*/
		return *this;
	}
	return *this;
}

/*Reallocating memory for vector. The function accepts quantity of new Type elements*/
template<class Type>
inline MyVector<Type>& MyVector<Type>::resize(long long _size)
{
	/*if less then 0 then just return *this  and if we changing size to the EXACT size then return *this*/
	if ((_size < 0) || (_size == this->size))
	{
		std::cout << "Cant resize vector." << std::endl;
		return *this;
	}
	/*if equal to 0 then just nullifying front/back ptrs*/
	if (_size == 0)
	{
		if (!this->empty())
		{
			this->clear();
		}
		this->front = this->data;
		this->back = this->data;
		this->size = 0;
		return *this;
	}

	/*if in range of prev size then just moving back ptr*/
	if (_size < this->size)
	{
		Type** newBack = this->front + _size;
		for (long long i = _size; i < this->size; i++)
		{
			delete this->front[i];
			this->front[i] = nullptr;
		}
		this->back = newBack;
		this->size = _size;
		return *this;
	}
	/*if above range of prev size then moving back ptr (up to capacity limit) and nullifying data*/
	if ((_size > this->size) && (_size <= this->capacity))
	{	
		try
		{
			/*nullifying future newly opened area*/
			for (int i = 0; i < (_size - this->size); i++)
			{
				this->front[this->size + i] = new Type;
				if (this->front[this->size + i] == nullptr)
				{
					this->size = this->size + i;
					this->back = this->front + this->size;
					throw MyException("Couldnt allocate memory in resize(long long _size) func. If above range of prev size and lower then capacity.") ;
				}
			}
			this->size = _size;
			this->back = this->front + this->size;
		}
		catch (const exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
		return *this;
	}
	/*if above range of prev capacity then allocating memory, nullifying data, and moving back ptr*/
	if (_size > this->capacity)
	{
		this->reserve(calcNewCapacity(_size));
		try
		{
			/*nullifying future newly opened area*/
			for (int i = 0; i < (_size - this->size); i++)
			{
				this->front[this->size + i] = new Type;
				if (this->front[this->size + i] == nullptr)
				{
					this->size = this->size + i;
					this->back = this->front + this->size;
					throw MyException("Couldnt allocate memory in resize(long long _size) func. If above range of prev size and higher then capacity.") ;
				}
			}
			this->size = _size;
			this->back = this->front + this->size;
		}
		catch (const exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
		return *this;
	}
	return *this;
}

/*Shrinking vector to size of size*/
template<class Type>
inline MyVector<Type>& MyVector<Type>::shrink_to_fit()
{
	this->reserve(this->size);
	return *this;
}

/*returns temp vector with elements in range of inputed indexes*/
template<class Type>
inline MyVector<Type> MyVector<Type>::getRange(long long _from, long long _to)
{
	MyVector<Type> temp;

	/*Looking if indexes in range of used part of vector*/
	if (((_from >= 0) && (_from <= (this->size - 1))) && ((_to >= 0) && (_to <= (this->size - 1))))
	{
		/*Case for one element*/
		if (_from == _to)
		{
			temp.reserve(1);
			temp.pushBack(*this->front[_from]);
			return temp;
		}
		if (_to < _from)
		{
			std::cout << "Warning! Right index is smaller than left index. Swapping." << std::endl;
			std::swap(_from, _to);
		}
		long long newSize = _to - _from + 1;
		temp.reserve(newSize);

		for (long long i = 0; i < temp.capacity; i++)
		{
			temp.pushBack(*this->front[_from + i]);
		}

		return temp;
	}
	else
	{
		std::cout << "Indexes is out of range in getRange func()" << std::endl;
		return temp;
	}
}

/*Deleting chosen element and returning element after deleted or last if chosen one is outside of vector*/
template<class Type>
inline MyVector<Type>& MyVector<Type>::erase(long long _index)
{
	erase(_index, _index);
	return *this;
}

/*Deleting range of element and returning element after deleted or last if chosen one is outside of vector*/
template<class Type>
inline MyVector<Type>& MyVector<Type>::erase(long long _from, long long _to)
{
	/*If empty then return*/
	if (this->front == this->back)
	{
		return *this;
	}
	if ((_from >= 0) && (_from < this->size) && (_to >= 0) && (_to < this->size))
	{
		if (_to < _from)
		{
			std::cout << "Warning! Right index is smaller than left index. Swapping." << std::endl;
			std::swap(_from, _to);
		}
		/*if range is equal to used part of vec then using clear()*/
		if ((_from == 0) && (_to == (this->size - 1)))
		{
			this->clear();
			return *this;
		}

		long long newSize = this->size - (_to - _from + 1);
		long long rightLen = this->size - _to - 1;			/*right part from erasing element/s. This part wil be shifted at the left.*/

		/*transporting data if needed*/
		for (long long i = _to + 1; i < rightLen; i++)
		{
			*this->front[_from + i] = std::move(*this->front[_to + 1 + i]);
		}

		/*deallocating memory of now unused elements (if needed and it WILL be needed at least one time)*/
		for (long long  i = newSize; i < this->size; i++)
		{
			delete this->front[i];
		}

		this->size = newSize;
		this->back = this->data + this->size;
	}
	else
	{
		std::cout << "Indexes is out of range" << std::endl;
	}

	return *this;
}

template<class Type>
inline bool MyVector<Type>::empty() const
{
	if (this->front == this->back)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class Type>
inline bool MyVector<Type>::isFree() const {
	if (this->data == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*Clearing Type element in vector*/
template<class Type>
inline MyVector<Type>& MyVector<Type>::clear()
{
	/*If not empty then clearing*/
	if (this->front != this->back)
	{
		for (int i = 0; i < this->size; i++)
		{
			delete this->front[i];
		}
		this->front = this->data;
		this->back = this->data;
		this->size = 0;
	}
	return *this;
}

template<class Type>
inline MyVector<Type>& MyVector<Type>::freeMyVector() {
	if (this->data != nullptr)
	{
		if ((this->front != this->data) || ((this->front + this->size) != this->back))
			/*if size is not equal to difference between back and front ptr then it is most likely to be uninitialised part of memory */
		{
			this->nullifyParams();
			return *this;
		}
		if (this->front != this->back)
		{
			this->clear();
		}
		delete[] this->data;
		this->capacity = 0;
		this->data = nullptr;
		this->front = nullptr;
		this->back = nullptr;
	}
	return *this;
}

/*Returns size of vector*/
template<class Type>
inline long long MyVector<Type>::getSize() const
{
	return this->size;
}

/*Returns capacity of vector*/
template<class Type>
inline long long MyVector<Type>::getCapacity() const
{
	return this->capacity;
}

template<class Type>
inline const Type& MyVector<Type>::operator[](long long _index) const
{
	if (this->front == this->back)
	{
		throw MyException("Vector is empty. Cant reach this index.") ;
	}
	if ((_index < 0) || (_index > (this->size - 1)))
	{
		throw MyException("Index is out of range. Cant reach this index.") ;
	}
	return *this->front[_index];
}

template<class Type>
inline Type& MyVector<Type>::operator[](long long _index)
{
	if (this->front == this->back)
	{
		throw MyException("Vector is empty. Cant reach this index.") ;
	}
	if ((_index < 0) || (_index > (this->size - 1)))
	{
		throw MyException("Index is out of range. Cant reach this index.") ;
	}
	return *this->front[_index];
}

template<class Type>
inline MyVector<Type>& MyVector<Type>::operator=(const MyVector<Type>& _myVector)
{
	/*if self equasion*/
	if (this == std::addressof(_myVector))
	{
		return *this;
	}
	/*if source vec is empty then we already did everything possible*/
	if (_myVector.front == _myVector.back)
	{
		this->freeMyVector();	/*Freeng vec*/
		return *this;
	}

	this->copyData(_myVector);
	return *this;
}

template<class Type>
inline MyVector<Type>& MyVector<Type>::operator=(MyVector<Type>&& _myVector) noexcept
{
	/*if self equasion*/
	if (this == std::addressof(_myVector))
	{
		return *this;
	}
	/*if source vec is empty then we already did everything possible*/
	if (_myVector.front == _myVector.back)
	{
		this->freeMyVector();	/*Freeng vec*/
		return *this;
	}
	this->freeMyVector();
	this->data = _myVector.data;
	this->front = _myVector.front;
	this->back = _myVector.back;
	this->size = _myVector.size;
	this->capacity = _myVector.capacity;
	_myVector.nullifyParams();

	return *this;
}

template<class Type>
inline MyVector<Type>& MyVector<Type>::operator+(const MyVector<Type>& _myVector)
{
	this->pushBack(_myVector);
	return *this;
}

template<class Type>
inline MyVector<Type>& MyVector<Type>::operator+(MyVector<Type>&& _myVector) noexcept
{
	this->pushBack(_myVector);
	return *this;
}

template<class Type>
inline void MyVector<Type>::destroy_in_place(Type& _obj)
{
	Type* obj = &_obj;
	/*if object is array then */
	if (std::is_array_v<Type>)
	{
		destroy_range(*obj, *(obj + std::extent_v<Type>));
	}
	else
	{
		_obj.~Type();
	}
}

template<class Type>
inline void MyVector<Type>::destroy_range(Type& _first, Type& _last)
{
	Type* first = &_first;
	Type* last = &_last;
	/*if Type has destructor then destroy it*/
	if (!std::is_trivially_destructible_v<Type>)
	{
		for (; first != last; first++)
		{
			destroy_in_place(*first);
		}
	}
}

template<class Type>
inline void MyVector<Type>::nullifyParams()
{
	this->data = nullptr;
	this->front = nullptr;
	this->back = nullptr;
	this->size = 0;
	this->capacity = 0;
}

template<class Type>
inline void MyVector<Type>::copyData(const MyVector<Type>& _myVector)
{
	this->freeMyVector();
	this->resize(_myVector.size);
	/*Cycle for copying data*/
	for (long long i = 0; i < _myVector.size; i++)
	{
		*this->front[i] = _myVector[i];
	}
	this->size = _myVector.size;
	this->back = this->front + this->size;
}

/*Returns a rounded up result of division of num and RESERVE_STEP and */
template<class Type>
long long MyVector<Type>::calcNewCapacity(long long num)
{	
	long long newCapacity = num;
	/*if after mod(num, RESERVE_STEP) result is NOT zero then changing capacity*/
	if ((abs(num % RESERVE_STEP) != 0))
	{
		newCapacity = (long long)(floor((1.0 * num / RESERVE_STEP) + 1) * RESERVE_STEP);
	}
	return newCapacity;
}


}	// myvec



#endif // !MYVECTOR_CPP


#endif // !MYVECTOR_H
