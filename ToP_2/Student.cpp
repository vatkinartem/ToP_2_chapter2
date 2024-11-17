#include "Student.h"
#include <string>
#include <iostream>

#ifndef STUDENT_CPP
#define STUDENT_CPP

using std::string;
using std::cout;
using std::endl;
using std::move;

void Student::nullifyParams()
{
	this->fio = "";
	this->marks.reserve(0);
	this->avgMark = 0.0;
}

/*Constructor of Default*/
Student::Student()
{
	this->avgMark = 0.0;
}

/*Constructor of Copy*/
Student::Student(const string& _fio, const MyVector<int>& _marks) : fio(_fio), marks(_marks)
{
	this->set_avgMark();
}

/*Constructor of Copy*/
Student::Student(const Student& _student) : fio(_student.fio), marks(_student.marks), avgMark(_student.avgMark)
{
}

/*Constructor of Move*/
Student::Student(Student&& _student) noexcept
{
	this->fio = move(_student.fio);
	this->marks = move(_student.marks);
	this->avgMark = move(_student.avgMark);
}

/*Destructor*/
Student::~Student()
{
}

void Student::moveSwap(Student& _source) noexcept
{
	Student temp(*this);
	*this = move(_source);
	_source = move(temp);
}

string Student::getClassName() const
{
	return string("Student");
}

string Student::getStr() const
{
	string _str = this->get_fio() + "/";
	_str += std::to_string(this->get_avgMark()) + "/";
	for (int i = 0; i < this->marks.getSize(); i++)
	{
		_str += std::to_string(this->marks[i]) + " ";
	}
	_str += "/";
	return _str;
}

string Student::get_fio() const
{
	return this->fio;
}

void Student::set_fio(const string& _fio)
{
	this->fio = _fio;
}

void Student::set_fio(string&& _fio) noexcept
{
	this->fio = std::move(_fio);
}

MyVector<int>& Student::get_marks() const
{
	return (MyVector<int>&)this->marks;
}

void Student::set_marks(const MyVector<int>& _marks)
{
	this->marks = _marks;
	this->set_avgMark();
}

void Student::set_marks(MyVector<int>&& _marks) noexcept
{
	this->marks = std::move(_marks);
	this->set_avgMark();
}

void Student::set_avgMark()
{
	double result = 0.0;
	long long size = this->marks.getSize();

	if (size == 0)
	{
		this->avgMark = result;
	}
	else
	{
		for (long long i = 0; i < size; i++)
		{
			result += this->marks[i];
		}
		result /= size;
		this->avgMark = result;
	}
}

double Student::get_avgMark() const
{
	return this->avgMark;
}

Student& Student::operator=(const Student& _student)
{
	this->fio = _student.fio;
	this->marks = _student.marks;
	this->avgMark = _student.avgMark;
	return *this;
}

Student& Student::operator=(Student&& _student) noexcept
{
	this->fio = std::move(_student.fio);
	this->marks = std::move(_student.marks);
	this->avgMark = std::move(_student.avgMark);
	return *this;
}

Student& Student::operator+(const MyVector<int>& _marks)
{
	this->marks.pushBack(_marks);
	
	this->set_avgMark();

	return *this;
}

Student& Student::operator+(MyVector<int>&& _marks) noexcept
{
	this->marks.pushBack(std::move(_marks));

	this->set_avgMark();

	return *this;
}

std::istream& operator>>(std::istream& is, Student& right)
{
	//int temp;
	//if (is >> temp)
	//	i = static_cast<COM::COM>(temp);
	//return is;

	return is;
}

std::ostream& operator<<(std::ostream& os, Student& right)
{
	std::string str;

	str += right.fio + " ";
	str += std::to_string(right.get_avgMark()) + " ";

	os << str;

	return os;
}

#endif // !STUDENT_CPP


