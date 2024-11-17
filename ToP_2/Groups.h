#pragma once
#include "MyVector.h"
#include "Group.h"

#ifndef GROUPS_H
#define GROUPS_H



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
    std::string getStr();

    MyVector<Group>& get_groups() const;
    void set_groups(const MyVector<Group>& _source);
    void set_groups(MyVector<Group>&& _source);

    Groups& operator=(const Groups& _source);
    Groups& operator=(Groups&& _source) noexcept;

    Groups& operator+=(const Group& _source);
    Groups& operator+=(Group&& _source) noexcept;

    Groups& operator+=(const Groups& _source);
    Groups& operator+=(Groups&& _source) noexcept;

    Group& operator[](long long index) const;
    Group& operator[](long long index);

    friend std::ostream& operator<< (std::ostream& os, Groups& right);
};



#endif // !GROUPS_H


