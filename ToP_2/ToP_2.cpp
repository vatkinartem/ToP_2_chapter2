#include <iostream>
#include <exception>
#include "MyVector.h"
#include "Groups.h"
#include "Menu.h"
#include "MyExceptions.h"


int main()
{
    using std::cout; using std::cin; using std::endl;

    Groups groups;
    Menu menu(&groups);

    menu.load();
    menu.start_Menu();

    return 1;
}
