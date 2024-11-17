#include "Menu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "MyExceptions.h"

using std::cout; using std::endl; using std::cin;

std::istream& operator>> (std::istream& is, COM& right) {
	int temp = 0;
	if (is >> temp)
		right = static_cast<COM>(temp);
	return is;
}

std::istream& operator>> (std::istream& is, VARS& right) {
	int temp = 0;
	if (is >> temp)
		right = static_cast<VARS>(temp);
	return is;
}

MyVector<string> extractFirstNWords(string str, char c0, int num) {
	MyVector<string> words;
	string temp = "";
	bool inWord = false;
	if (str[str.size() - 1] != '\n')
	{
		str.push_back('\n');
	}
	for (char c : str)
	{
		if ((c != c0) && (c != '\n') && (c != '\0'))
		{
			inWord = true;
			temp += c;
			continue;
		}
		if ((inWord) && ((c == c0) || (c == '\n') || (c == '\0')))
		{
			words.pushBack(std::move(temp));
			inWord = false;
			if (words.getSize() == num)
			{
				break;
			}
		}
	}
	return words;
}

MyVector<int> strVecToIntVec(const MyVector<string>& marks_s)
{
	MyVector<int> marks_i;

	for (long long i = 0; i < marks_s.getSize(); i++)
	{
		try
		{
			marks_i.pushBack((int)atof(marks_s[i].c_str()));
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
	}

	return marks_i;
}

Group Menu::parseString(std::string str)
{
	Student temp_stud;
	Group temp_group;
	MyVector<string> field;		
	MyVector<string> marks_s;	
	MyVector<int> marks_i;		

	field = std::move(extractFirstNWords(str, '/', 3));			/*we have to extract three field between "/"*/

	/*checking if we got at least three fiealds and first and second must not be empty*/
	if ((field.getSize() < 3) || (field[0].empty()) || (field[1].empty()))
	{
		throw MyException("Invalid string. Not enought fields or wrong first and second.");
	}

	marks_s = std::move(extractFirstNWords(field[2], ' ', -1));	/*extracting marks as string " ". It is very expensive operation because of array of pointer that pointing to elements*/

	marks_i = std::move(strVecToIntVec(marks_s));				/*transforming marks_s into mark_i*/

	marks_s.freeMyVector();		/*Because of expensiveness we freeing vector as soon as possible*/

	temp_stud.set_fio(field[1]);
	temp_stud.set_marks(std::move(marks_i));
	temp_group.set_groupNumber(field[0]);

	temp_group.get_students().pushBack(std::move(temp_stud));
	temp_group.set_avgMark();

	return temp_group;
}

Menu::Menu()
{
	this->groups = nullptr;
}

Menu::Menu(Groups* groups)
{
	this->groups = groups;
}

Menu::~Menu()
{
}


Groups Menu::search_by_name()
{
	Groups temp_groups;
	/*not emplemented*/
	return (Groups&&)temp_groups;
}

Groups Menu::search_by_greater_mark(long long number)
{
	Groups temp_groups;
	Group temp_group;
	long long groupsNum = this->groups->get_groups().getSize();	/*Qantity of groups*/
	long long studentsNum = 0;									/*Qantity of student in current group*/

	/*for each group in groups*/
	for (long long i = 0; i < groupsNum; i++)
	{
		studentsNum = this->groups->get_groups()[i].get_students().getSize();
		temp_group.set_groupNumber("");
		temp_group.get_students().freeMyVector();
		temp_group.get_subjects().freeMyVector();
		temp_group.set_avgMark();

		temp_group.set_groupNumber(this->groups->get_groups()[i].get_groupNumber());	/*remembering name of group we currently looking*/
		/*for each student in group*/
		for (long long j = 0; j < studentsNum; j++)
		{
			/*if avg mark bigger then wanted then adding this student to temp vec*/
			if (this->groups->get_groups()[i].get_students()[j].get_avgMark() >= number)		
			{
				temp_group.get_students().pushBack(this->groups->get_groups()[i].get_students()[j]);	/*rememvering needed student*/
			}
		}
		/*if we have atleast 1 student*/
		if (temp_group.get_students().getSize() > 0)
		{
			temp_group.set_avgMark();
			temp_groups += std::move(temp_group);
		}
	}

	return (Groups&&)temp_groups;
}

Groups Menu::search_by_lesser_mark()
{
	Groups temp_groups;
	/*not emplemented*/
	return (Groups&&)temp_groups;
}

void Menu::start_Menu()
{
    COM command = COM::DEFAULT;

    this->help();

    do
    {
        try
		{
			command = COM::DEFAULT;

            cout << "Awaiting command..." << endl;
            cin >> command;

            if (cin.fail())
            {
                throw MyException("Non numerical input found");
            }

            switch (command)
            {
            case DEFAULT:
				cout << "Invalid command" << endl;
                break;
            case HELP:
                this->help();
                break;
            case INPUT:
                this->input();
                break;
            case PRINTSPEC:
				this->printspec();
                break;
			case PRINTALL:
				this->printall();
				break;
			case LOAD:
				this->load();
				break;
			case DELETE:
				this->delete_elem();
				break;
			case EDIT:
				this->edit();
				break;
            case EXIT:
				cout << "Exit prrogram" << endl;
                break;
            }
        }
        catch (const std::exception& ex)
        {
            cin.clear();
            char c;
            cin >> c;
            cout << ex.what() << endl;
        }

    } while (command != COM::EXIT);

	this->excercise2();

}

void Menu::excercise2()
{
	string left;
	string right;
	string str;
	std::ifstream in;		/*to temporary storage parced data*/
	std::stringstream ss;

	try
	{
		cout << "Starting Excercise 2" << endl;

		in.open("2.txt", std::ios::in);

		while (getline(in, str, '\n'))
		{
			ss << str;

			while (!ss.eof())
			{
				left.clear();
				right.clear();

				ss >> left;
				ss >> right;

				if (right.empty())
				{
					cout << left;
					continue;
				}

				cout << right << " " << left << " ";
			}
			ss.clear();
			cout << endl;
		}

		cout << "\nExcercise 2 finished\n" << endl;
		in.close();
	}
	catch (const exception& ex)
	{
		ss.clear();
		char c;
		ss >> c;
		in.close();
		cout << ex.what() << endl;
	}
}

void Menu::set_groups(Groups* groups)
{
	this->groups = groups;
}

void Menu::help()
{
	cout << COM::HELP << " - help\n"
		<< COM::INPUT << " - input\n"
		<< COM::PRINTSPEC << " - print avg >= 4\n"
		<< COM::PRINTALL << " - print all\n"
		<< COM::LOAD << " - load\n"
		<< COM::DELETE << " - delete\n"
		<< COM::EDIT << " - edit\n"
		<< COM::EXIT << " - exit\n"
		<< endl;
}

void Menu::input()
{
	string temp_string;
	string part_string;
	Group temp_group;
	char ch;

	try
	{
		cout << "Input one string that represents student (group_number/familia I.O./mark0 mark1 mark2/)" << endl;
		cin.clear();

		while (cin >> part_string)
		{
			temp_string += part_string + " ";
			ch = cin.peek();
			if (ch == '\n')
			{
				break;
			}
		}

		if (cin.fail())
		{
			throw MyException("Cant get string");
		}

		temp_group = std::move(parseString(temp_string));

		*this->groups += std::move(temp_group);

		cout << "Input from console succefully finished\n" << endl;
	}
	catch (const exception& ex)
	{
		cin.clear();
		char c;
		cin >> c;
		cout << ex.what() << endl;
	}
}

void Menu::printspec()
{
	Groups students;
	students = std::move(this->search_by_greater_mark(4));
	if (students.get_groups().getSize() == 0)
	{
		cout << "There is no such students" << endl;
	}
	/*for each group in groups*/
	for (long long i = 0; i < students.get_groups().getSize(); i++)
	{
		/*for each student*/
		for (long long j = 0; j < students.get_groups()[i].get_students().getSize(); j++)
		{
			cout << students.get_groups()[i].get_groupNumber();
			cout << students.get_groups()[i].get_students()[j] << endl;
		}
	}
}

void Menu::printall()
{
	if (this->groups->get_groups().getSize() > 0)
	{
		std::cout << *this->groups;
	}
	else
	{
		cout << "Nothing to print. Empty group list." << endl;
	}
	
}

void Menu::load()
{
	string ans;
	string str;
	std::ifstream in;		/*to temporary storage parced data*/
	int total_entries = 0;

	try
	{
		cout << "Are you sure you want to load from \"base.txt\" ?" << endl;
		cout << "Load base? [y/n]" << endl;

		cin >> ans;
		if (cin.fail())
		{
			throw MyException("Cant convert to string.");
		}
		if ((ans != "y") && (ans != "n"))
		{
			throw MyException("Wrong input. It has to be \"y\" or \"n\" ");
		}
		if (ans == "n")
		{
			return;
		}

		in.open("base.txt", std::ios::in);

		this->groups->get_groups().freeMyVector();

		while (getline(in, str, '\n'))
		{
			try
			{
				add_entry(str);
				total_entries++;
			}
			catch (const exception& ex)
			{
				cout << ex.what() << endl;
			}
		}

		cout << "Loading from file \"base.txt\" has been completed." << endl;
		cout << "Added " << total_entries << " entries\n" << endl;
		in.close();
	}
	catch (const exception& ex)
	{
		cin.clear();
		char c;
		cin >> c;
		cout << ex.what() << endl;
		cout << "Added " << total_entries << " entries\n" << endl;
	}

}

void Menu::delete_elem()
{
	long long group_index = -1;
	long long stud_index = -1;
	VARS var = VARS::NONE;
	try
	{
		cout << "Input type of element to be deleted (0 - None, 1 - Groups, 2 - Group, 3 - Student)" << endl;
		cin >> var;
		cin.clear();
		if (var == VARS::NONE)
		{
			cout << "Cancelling operation" << endl;
			return;
		}
		else if (var == VARS::GROUPS)
		{
			cout << "Group mode selected.\nDeleting all groups" << endl;
			this->groups->get_groups().freeMyVector();
		} 
		else if (var == VARS::GROUP)
		{
			cout << "Group mode selected.\nChoose index of the group" << endl;
			cin >> group_index;
			if (cin.fail())
			{
				throw MyException("Failed to parse a string to integer");
			}

			this->groups->get_groups().erase(group_index);
		}
		else if (var == VARS::STUDENT)
		{
			cout << "Student mode selected.\nChoose index of the group in which student is" << endl;
			cin >> group_index;
			if (cin.fail())
			{
				throw MyException("Failed to parse a string to integer");
			}

			cout << "Choose index of the student in this group " << group_index << endl;
			cin >> stud_index;
			if (cin.fail())
			{
				throw MyException("Failed to parse a string to integer");
			}

			this->groups->get_groups()[group_index].get_students().erase(stud_index);
			this->groups->get_groups()[group_index].set_avgMark();						/*recalculating avgMark in this group*/
		}
		cout << "Completed" << endl;
	}
	catch (const std::exception& ex)
	{
		cin.clear();
		char c;
		cin >> c;
		cout << ex.what() << endl;
	}
}

void Menu::edit()
{
	Group temp_group;
	std::string temp_str;
	std::string part_temp_str;
	long long group_index = -1;
	long long stud_index = -1;
	VARS var = VARS::NONE;
	try
	{
		cout << "Input type of element to be edited (0 - None, 2 - Group, 3 - Student)" << endl;
		cin >> var;
		cin.clear();
		if (var == VARS::NONE)
		{
			cout << "Cancelling operation" << endl;
			return;
		}
		else if (var == VARS::GROUP)
		{
			cout << "Group mode selected.\nChoose index of the group" << endl;
			cin >> group_index;
			if (cin.fail())
			{
				throw MyException("Failed to parse a string to integer");
			}

			cout << "Choose new number of group (string)" << endl;
			cin >> temp_str;
			cin.clear();

			this->groups->get_groups()[group_index].set_groupNumber(temp_str);
		}
		else if (var == VARS::STUDENT)
		{
			cout << "Student mode selected.\nChoose index of the group in which student is" << endl;
			cin >> group_index;
			if (cin.fail())
			{
				throw MyException("Failed to parse a string to integer");
			}
			if ((group_index < 0) || (group_index >= this->groups->get_groups().getSize()))
			{
				throw MyException("Index out of range");
			}

			cout << "Input index of the student in this group " << group_index << endl;
			cin >> stud_index;
			if (cin.fail())
			{
				throw MyException("Failed to parse a string to integer");
			}
			if ((stud_index < 0) || (stud_index >= this->groups->get_groups()[group_index].get_students().getSize()))
			{
				throw MyException("Index out of range");
			}
			temp_str += this->groups->get_groups()[group_index].get_groupNumber() + "/";

			cout << "Input new data of the student (fio/mark1 mark2 mark3/)" << endl;
			while (cin >> part_temp_str)
			{
				temp_str += part_temp_str + " ";
				if (cin.peek() == '\n')
				{
					break;
				}
			}
			if (cin.fail())
			{
				throw MyException("Failed to parse a string to string");
			}

			temp_group = std::move(parseString(temp_str));
			if (temp_group.get_students().getSize() <= 0)
			{
				throw MyException("After parse somehow got back an empty group");
			}

			this->groups->get_groups()[group_index].get_students()[stud_index].set_fio(std::move(temp_group.get_students()[0].get_fio()));
			this->groups->get_groups()[group_index].get_students()[stud_index].set_marks(std::move(temp_group.get_students()[0].get_marks()));
			this->groups->get_groups()[group_index].get_students()[stud_index].set_avgMark();
			this->groups->get_groups()[group_index].set_avgMark();						/*recalculating avgMark in this group*/
		}
		cout << "Completed" << endl;
	}
	catch (const std::exception& ex)
	{
		cin.clear();
		char c;
		cin >> c;
		cout << ex.what() << endl;
	}
}

void Menu::add_entry(const std::string& str)
{
	Group temp_group;

	try
	{
		temp_group = std::move(parseString(str));

		for (long long i = 0; i < this->groups->get_groups().getSize(); i++)
		{
			if (temp_group.get_groupNumber() == groups->get_groups()[i].get_groupNumber())
			{
				groups->get_groups()[i] += std::move(temp_group);
				groups->get_groups()[i].set_avgMark();
				break;
			}
		}

		if (temp_group.get_students().getSize() > 0)
		{
			temp_group.set_avgMark();
			groups->get_groups().pushBack(std::move(temp_group));
		}

		cout << "Added one entry" << endl;
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
	}
}
