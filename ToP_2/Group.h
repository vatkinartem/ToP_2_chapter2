#pragma once
#include "MyVector.h"
#include "Student.h"
#include <iostream>

#ifndef GROUP_H
#define GROUP_H



class Group
{
	struct Data
	{
		MyVector<Student> students;
		MyVector<std::string> subjects;
		std::string groupNumber;
		double avgMark;

		Data() : avgMark(0), groupNumber(), subjects(), students() {}
		Data(Data& source) : avgMark(source.avgMark), groupNumber(source.groupNumber), subjects(source.subjects), students(source.students) {}
		Data(Data&& source) noexcept : avgMark(std::move(source.avgMark)), groupNumber(std::move(source.groupNumber)), subjects(std::move(source.subjects)), students(std::move(source.students)) {}
		~Data() {}

		Data& operator=(const Data& source) {
			avgMark = source.avgMark;
			groupNumber = source.groupNumber;
			subjects = source.subjects;
			students = source.students;
		}
		Data& operator=(Data&& source) noexcept {
			avgMark = std::move(source.avgMark);
			groupNumber = std::move(source.groupNumber);
			subjects = std::move(source.subjects);
			students = std::move(source.students);
		}
	};
private:
	Data* data;

public:
	Group();
	Group(const string& _groupNumber, const MyVector<string>& subjects, const MyVector<Student>& students);
	Group(const Group& _source);
	Group(Group&& _source) noexcept;
	virtual ~Group();
	std::string getStr();

	Group& get_data() const;
	double get_avgMark() const;
	void set_avgMark();
	string& get_groupNumber() const;
	void set_groupNumber(const string& _groupNumber);
	MyVector<string>& get_subjects() const;
	void set_subjects(const MyVector<string>& _subjects);
	MyVector<Student>& get_students() const;
	void set_students(const MyVector<Student>& _students);

	Group& operator=(const Group& _source);
	Group& operator=(Group&& _source) noexcept;

	Group& operator+(const Student& _source);
	Group& operator+(Student&& _source) noexcept;

	Group& operator+(const Group& _source);
	Group& operator+(Group&& _source) noexcept;

	Group& operator[](long long index) const;
	Group& operator[](long long index);

	friend std::istream& operator>> (std::istream& is, Group& right);
	friend std::ostream& operator<< (std::ostream& os, Group& right);
};



#endif // !GROUP_H

