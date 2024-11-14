#pragma once
#include "MyVector.h"
#include "Group.h"

class Groups
{
    friend Group;
private:
    MyVector<Group> groups;
public:
    Groups();
    Groups(const Groups& _source);
    Groups(Groups&& _source) noexcept;
    virtual ~Groups();

    MyVector<Student>& search_by_name();                            /*since it iss not on the list then i wont do it. Dont wonna waste time*/
    MyVector<Student>& search_by_greater_mark(long long number);
    MyVector<Student>& search_by_lesser_mark();                     /*since it iss not on the list then i wont do it. Dont wonna waste time*/

    Groups& operator=(const Groups& _source);
    Groups& operator=(Groups&& _source) noexcept;

    Groups& operator+(const Student& _source);
    Groups& operator+(Student&& _source) noexcept;

    Group& operator[](long long index) const;
    Group& operator[](long long index);
};

