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

Groups& Groups::operator+=(const Group& _source)
{
	bool match_found = false;

	for (long long i = 0; i < this->get_groups().getSize(); i++)
	{
		if (this->groups[i].get_groupNumber() == _source.get_groupNumber())
		{
			match_found = true;
			this->groups[i].get_students().pushBack(_source.get_students());
			this->groups[i].set_avgMark();		/*recalculating avgMark*/
			break;
		}
	}

	if (match_found == false)
	{
		this->get_groups().pushBack(_source);
	}
	return *this;
}

Groups& Groups::operator+=(Group&& _source) noexcept
{
	bool match_found = false;

	for (long long i = 0; i < this->get_groups().getSize(); i++)
	{
		if (this->groups[i].get_groupNumber() == _source.get_groupNumber())
		{
			match_found = true;
			this->groups[i].get_students().pushBack(std::move(_source.get_students()));
			this->groups[i].set_avgMark();		/*recalculating avgMark*/
			break;
		}
	}
	if (match_found == false)
	{
		this->get_groups().pushBack(std::move(_source));
	}
	return *this;
}

Groups& Groups::operator+=(const Groups& _source)
{
	long long source_size = _source.groups.getSize();
	for (long long i = 0; i < source_size; i++)
	{
		*this += _source.groups[i];
	}
	return *this;
}

Groups& Groups::operator+=(Groups&& _source) noexcept
{
	long long source_size = _source.groups.getSize();
	for (long long i = 0; i < source_size; i++)
	{
		*this += std::move(_source.groups[i]);
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
