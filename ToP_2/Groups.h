#pragma once
#include "MyVector.h"
#include "Group.h"

class Groups :
    public Group
{
private:
    MyVector<Group> groups;
public:
    Groups();
    Groups(const Groups& _source);
    Groups(Groups&& _source);
    virtual ~Groups();

    /*some overloaded functions with = []*/
};

