#pragma once
#include "MyVector.h"

#ifndef STUDENT_H
#define STUDENT_H


using std::string;
using myvec::MyVector;

class Student
{
private:
    string fio;
    MyVector<long long> marks;

    void nullifyParams();
public:
    Student();
    Student(const string& _fio, const MyVector<long long>& _marks);
    Student(const Student& _student);
    Student(Student&& _student) noexcept;
    virtual ~Student();
    void moveSwap(Student& _source) noexcept;
    string getClassName() const;
    string getStr() const;

    string get_fio() const;
    void set_fio(const string& _fio);
    void set_fio(string&& _fio) noexcept;
    MyVector<long long>& get_marks () const;
    void set_marks (const MyVector<long long>& _marks);
    void set_marks (MyVector<long long>&& _marks) noexcept;

    Student& operator= (const Student& _student);
    Student& operator= (Student&& _student) noexcept;
};



#endif // !STUDENT_H

