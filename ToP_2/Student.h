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
    MyVector<int> marks;
    double avgMark;

    void nullifyParams();
public:
    Student();
    Student(const string& _fio, const MyVector<int>& _marks);
    Student(const Student& _student);
    Student(Student&& _student) noexcept;
    virtual ~Student();
    void moveSwap(Student& _source) noexcept;
    string getClassName() const;
    string getStr() const;

    string get_fio() const;
    void set_fio(const string& _fio);

    void set_fio(string&& _fio) noexcept;
    MyVector<int>& get_marks () const;

    void set_marks (const MyVector<int>& _marks);
    void set_marks (MyVector<int>&& _marks) noexcept;

    void set_avgMark();             /*calculates avgMark and puts result in avgMark*/
    double get_avgMark() const;

    Student& operator= (const Student& _student);
    Student& operator= (Student&& _student) noexcept;

    Student& operator+ (const MyVector<int>& _marks);         /*adding marks and recalculating avgMark*/
    Student& operator+ (MyVector<int>&& _marks) noexcept;     /*adding marks and recalculating avgMark*/

    friend std::istream& operator>> (std::istream& is, Student& right);
    friend std::ostream& operator<< (std::ostream& os, Student& right);
};



#endif // !STUDENT_H


