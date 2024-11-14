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
}

/*Constructor of Default*/
Student::Student()
{
#ifdef _DEBUG
	std::cout << " " << this->getClassName() << "() with adress " << this << std::endl;
#endif // _DEBUG
}

/*Constructor of Copy*/
Student::Student(const string& _fio, const MyVector<long long>& _marks) : fio(_fio), marks(_marks)
{
#ifdef _DEBUG
	std::cout << " " << this->getClassName() << "() with adress " << this << std::endl;
#endif // _DEBUG
}

/*Constructor of Copy*/
Student::Student(const Student& _student) : fio(_student.fio), marks(_student.marks)
{
#ifdef _DEBUG
	std::cout << " " << this->getClassName() << "() with adress " << this << std::endl;
#endif // _DEBUG
}

/*Constructor of Move*/
Student::Student(Student&& _student) noexcept
{
	this->fio = move(_student.fio);
	this->marks = move(_student.marks);
#ifdef _DEBUG
	std::cout << " " << this->getClassName() << "() with adress " << this << std::endl;
#endif // _DEBUG
}

/*Destructor*/
Student::~Student()
{
#ifdef _DEBUG
	std::cout << "~" << this->getClassName() << "() with adress " << this << std::endl;
#endif // _DEBUG
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
	string _str = this->getClassName() + "/" + this->get_fio() + "/";
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
	this->fio = move(_fio);
}

MyVector<long long>& Student::get_marks() const
{
	return (MyVector<long long>&)this->marks;
}

void Student::set_marks(const MyVector<long long>& _marks)
{
	this->marks = _marks;
}

void Student::set_marks(MyVector<long long>&& _marks) noexcept
{
	this->marks = move(_marks);
}

Student& Student::operator=(const Student& _student)
{
	this->fio = _student.fio;
	this->marks = _student.marks;
	return *this;
}

Student& Student::operator=(Student&& _student) noexcept
{
	this->fio = move(_student.fio);
	this->marks = move(_student.marks);
	return *this;
}


#endif // !STUDENT_CPP


