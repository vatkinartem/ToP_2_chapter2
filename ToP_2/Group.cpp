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

std::string Group::getStr()
{
	std::string str;
	long long cur_size = this->data->students.getSize();
	long long cur_marks_size = 0;

	for (long long i = 0; i < cur_size; i++)
	{
		str += this->data->groupNumber + "/";
		str += this->data->students[i].getStr();
		str += "/\n";
	}

	return str;
}

Group::Data& Group::get_data() const
{
	return (Group::Data&)*this->data;
}

double Group::get_avgMark() const
{
	return this->data->avgMark;
}

void Group::set_avgMark()
{
	double result = 0.0;
	double cur_sumOfMarks = 0.0;
	double cur_numOfMarks = 0.0;
	long long cur_size = this->data->students.getSize();

	if (cur_size == 0)
	{
		this->data->avgMark = result;
	}

	for (long long i = 0; i < cur_size; i++)
	{
		cur_numOfMarks += this->data->students[i].get_marks().getSize();
		cur_sumOfMarks += round(this->data->students[i].get_avgMark() * this->data->students[i].get_marks().getSize());
	}
	result = cur_sumOfMarks / cur_numOfMarks;
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
	this->set_avgMark();				/*recalculating avgMark*/
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

Group& Group::operator+=(const Student& _source)
{
	long long source_marks_num = _source.get_marks().getSize();
	this->data->students.pushBack(_source);
	if (source_marks_num > 0)
	{
		this->set_avgMark();
	}

	return *this;
}

Group& Group::operator+=(Student&& _source) noexcept
{
	long long source_marks_num = _source.get_marks().getSize();
	this->data->students.pushBack(std::move(_source));
	if (source_marks_num > 0)
	{
		this->set_avgMark();
	}

	return *this;
}

Group& Group::operator+=(const Group& _source)
{
	long long source_size = _source.get_students().getSize();
	this->data->students.pushBack(_source.get_students());
	if (source_size > 0)
	{
		this->set_avgMark();
	}

	return *this;
}

Group& Group::operator+=(Group&& _source) noexcept
{
	long long source_size = _source.get_students().getSize();
	this->data->students.pushBack(std::move(_source.get_students()));
	if (source_size > 0)
	{
		this->set_avgMark();
	}

	return *this;
}

Group& Group::operator[](long long index) const
{
	if (this->data->students.empty())
	{
		throw MyException("Empty vector. Cant acces this index.");
	}
	if ((index < 0) || (index >= this->data->students.getSize()))
	{
		throw MyException("Index is out of range");
	}
	return (Group&)this->data->students[index];
}

Group& Group::operator[](long long index)
{
	if (this->data->students.empty())
	{
		throw MyException("Empty vector. Cant acces this index.");
	}
	if ((index < 0) || (index >= this->data->students.getSize()))
	{
		throw MyException("Index is out of range");
	}
	return (Group&)this->data->students[index];
}

std::ostream& operator<<(std::ostream& os, Group& right)
{
	std::string str;
	long long cur_size = right.data->students.getSize();
	str += std::string("Group: ") + right.data->groupNumber + "\n";
	str += std::string("Average mark: ") + std::to_string(right.data->avgMark) + "\n";
	for (long long i = 0; i < cur_size; i++)
	{
		str += right.data->groupNumber + "/";
		str += right.data->students[i].get_fio() + "/";
		str += std::to_string(right.data->students[i].get_avgMark()) + "/\n";
	}

	os << str;

	return os;
}



#endif // !GROUP_CPP
