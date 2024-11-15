#include "Groups.h"
#include "MyExceptions.h"



#ifndef GROUPS_CPP
#define GROUPS_CPP



Groups::Groups()
{
}

Groups::Groups(const Groups& _source)
{
	this->groups = _source.groups;
}

Groups::Groups(Groups&& _source) noexcept
{
	this->groups = std::move(_source.groups);
}

Groups::~Groups()
{
}

std::string Groups::getStr()
{
	std::string str;
	long long num_of_groups = this->groups.getSize();
	for (long long i = 0; i < num_of_groups; i++)
	{
		str += this->groups[i].getStr();
	}

	return str;
}

MyVector<Student> Groups::search_by_name()
{
	/*not emplemented*/
	return (MyVector<Student>&&)MyVector<Student>();
}

MyVector<Student> Groups::search_by_greater_mark(long long number)
{
	MyVector<Student> temp;
	long long groupsNum = this->groups.getSize();	/*Qantity of groups*/
	long long studentsNum = 0;						/*Qantity of student in current group*/

	for (long long i = 0; i < groupsNum; i++)
	{
		studentsNum = this->groups[i].get_students().getSize();

		for (long long j = 0; j < studentsNum; j++)
		{
			if (this->groups[i].get_students()[j].get_avgMark() >= number)		/*if avg mark bigger then wanted then adding this student to temp vec*/
			{
				temp.pushBack(this->groups[i].get_students()[j]);
			}
		}
	}

	return (MyVector<Student>&&)temp;
}

MyVector<Student> Groups::search_by_lesser_mark()
{
	/*not emplemented*/
	return (MyVector<Student>&&)MyVector<Student>();
}

MyVector<Group>& Groups::get_groups() const
{
	return (MyVector<Group>&)this->groups;
}

void Groups::set_groups(const MyVector<Group>& _source)
{
	this->groups = _source;
}

void Groups::set_groups(MyVector<Group>&& _source)
{
	this->groups = std::move(_source);
}

Groups& Groups::operator=(const Groups& _source)
{
	this->groups = _source.groups;
	return *this;
}

Groups& Groups::operator=(Groups&& _source) noexcept
{
	this->groups = std::move(_source.groups);
	return *this;
}

Groups& Groups::operator+(const Group& _source)
{
	this->groups.pushBack(_source);
	return *this;
}

Groups& Groups::operator+(Group&& _source) noexcept
{
	this->groups.pushBack(std::move(_source));
	return *this;
}

Groups& Groups::operator+(const Groups& _source)
{
	long long source_size = _source.groups.getSize();
	for (long long i = 0; i < source_size; i++)
	{
		this->groups.pushBack(_source.groups[i]);
	}
	return *this;
}

Groups& Groups::operator+(Groups&& _source) noexcept
{
	long long source_size = _source.groups.getSize();
	for (long long i = 0; i < source_size; i++)
	{
		this->groups.pushBack(std::move(_source.groups[i]));
	}
	return *this;
}

Group& Groups::operator[](long long index) const
{
	if (this->groups.empty())
	{
		throw MyException("Empty vector. Cant acces this index.");
	}
	if ((index < 0) || (index >= this->groups.getSize()))
	{
		throw MyException("Index is out of range");
	}

	return (Group&)this->groups[index];
}

Group& Groups::operator[](long long index)
{
	if (this->groups.empty())
	{
		throw MyException("Empty vector. Cant acces this index.");
	}
	if ((index < 0) || (index >= this->groups.getSize()))
	{
		throw MyException("Index is out of range");
	}

	return this->groups[index];
}

std::istream& operator>>(std::istream& is, Groups& right)
{


	return is;
}

std::ostream& operator<<(std::ostream& os, Groups& right)
{
	std::string str;
	long long num_of_groups = right.groups.getSize();
	/*for each group in groups*/
	for (long long i = 0; i < num_of_groups; i++)
	{
		os << right.groups[i];
	}

	return os;
}



#endif	//GROUPS_CPP
