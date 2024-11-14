#include "Group.h"

#ifndef GROUP_CPP
#define GROUP_CPP



Group::Group()
{
	this->data = new Data;
}

Group::Group(const string& _groupNumber, const MyVector<string>& subjects, const MyVector<Student>& students)
{
	this->data = new Data;
	this->data->groupNumber = _groupNumber;
	this->data->subjects = subjects;
	this->data->students = students;
	this->set_avgMark();
}

Group::Group(const Group& _source)
{
	this->data = new Data;
	this->data->avgMark = _source.data->avgMark;
	this->data->groupNumber = _source.data->groupNumber;
	this->data->subjects = _source.data->subjects;
	this->data->students = _source.data->students;
}

Group::Group(Group&& _source) noexcept
{
	this->data = new Data;
	this->data->avgMark = std::move(_source.data->avgMark);
	this->data->groupNumber = std::move(_source.data->groupNumber);
	this->data->subjects = std::move(_source.data->subjects);
	this->data->students = std::move(_source.data->students);
}

Group::~Group()
{
	delete this->data;
}

double Group::get_avgMark() const
{
	return (double)this->data->avgMark;
}

void Group::set_avgMark()
{
	double result = 0.0;
	long long size = this->data->students.getSize();

	for (long long i = 0; i < size; i++)
	{
		result += this->data->students[i].get_avgMark();
	}
	result /= size;
	this->data->avgMark = result;
}

std::string& Group::get_groupNumber() const
{
	return this->data->groupNumber;
}

void Group::set_groupNumber(const string& _groupNumber)
{
	this->data->groupNumber = _groupNumber;
}

MyVector<string>& Group::get_subjects() const
{
	return (MyVector<string>&)this->data->subjects;
}

void Group::set_subjects(const MyVector<string>& _subjects)
{
	this->data->subjects = _subjects;
}

MyVector<Student>& Group::get_students() const
{
	return (MyVector<Student>&)this->data->students;
}

void Group::set_students(const MyVector<Student>& _students)
{
	this->data->students = _students;
	this->set_avgMark();
}

Group& Group::operator=(const Group& _source)
{
	/*checking on selfcopy*/
	if (std::addressof(_source) == this)
	{
		return *this;
	}
	this->data->avgMark = _source.data->avgMark;
	this->data->groupNumber = _source.data->groupNumber;
	this->data->subjects = _source.data->subjects;
	this->data->students = _source.data->students;
	return *this;
}

Group& Group::operator=(Group&& _source) noexcept
{
	/*checking on selfmove*/
	if (std::addressof(_source) == this)
	{
		return *this;
	}
	this->data->avgMark = std::move(_source.data->avgMark);
	this->data->groupNumber = std::move(_source.data->groupNumber);
	this->data->subjects = std::move(_source.data->subjects);
	this->data->students = std::move(_source.data->students);
	return *this;
}

Group& Group::operator+(const Student& _source)
{
	// TODO: вставьте здесь оператор return
	return *this;
}

Group& Group::operator+(Student&& _source) noexcept
{
	// TODO: вставьте здесь оператор return
	return *this;
}

Group& Group::operator+(const Group& _source)
{
	// TODO: вставьте здесь оператор return
	return *this;
}

Group& Group::operator+(Group&& _source) noexcept
{
	// TODO: вставьте здесь оператор return
	return *this;
}

std::istream& Group::operator>>(std::istream& is)
{
	return is;
}

std::ostream& Group::operator<<(std::ostream& os)
{
	return os;
}




#endif // !GROUP_CPP

