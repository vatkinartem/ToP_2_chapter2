#include "Groups.h"

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

MyVector<Student>& Groups::search_by_greater_mark(long long number)
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

	return temp;
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

Groups& Groups::operator+(const Student& _source)
{
	/*todo*/
	return *this;
}

Groups& Groups::operator+(Student&& _source) noexcept
{
	/*todo*/
	return *this;
}

Group& Groups::operator[](long long index) const
{
	return (Group&)this->groups[index];
}

Group& Groups::operator[](long long index)
{
	return this->groups[index];
}
