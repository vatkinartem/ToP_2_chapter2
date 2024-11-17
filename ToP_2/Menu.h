#pragma once
#include "Groups.h"

enum COM
{
	DEFAULT,
	HELP,
	INPUT,
	PRINTSPEC,
	PRINTALL,
	LOAD,
	EXIT
};

class Menu
{
	friend MyVector<string> extractFirstNWords(string str, char c0, int num);
	friend MyVector<int> strVecToIntVec(const MyVector<string>& marks_s);
	friend std::istream& operator>> (std::istream& is, COM& right);
private:
	Group parseString(std::string str);
public:
	Groups* groups;

	Menu();
	Menu(Groups* groups);
	virtual ~Menu();

	Groups search_by_name();                            /*since it is not on the list then i wont do it. Dont wonna waste time*/
	Groups search_by_greater_mark(long long number);    /*As says name of function it finds all student with required avgMark and returns vetor of this students*/
	Groups search_by_lesser_mark();                     /*since it is not on the list then i wont do it. Dont wonna waste time*/

	void start_Menu();
	void excercise2();
	void set_groups(Groups* groups);
	void help();
	void input();
	void print();
	void load();
	void add_entry(const std::string& str);
};
