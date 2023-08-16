#include "std_lib_facilities.h"
#include "skiplists.h"
#include <chrono>
#include <ctime>
// #include <Windows.h> commented this out since it threw an error
#include <stdio.h>

int main()


{
	//EXAMPLE 
	int secs = time(0);
	srand(secs);
	skiplists* list = new skiplists(3);
	int temp;
	cout << "---- INSERTION PHASE ----\n";
	while (cin >> temp && temp != 0)
	{
		list->add(temp);
		list->print_all();
	}
	cout << "---- DELETION PHASE ----\n";
	while (cin >> temp && temp != 0) {
		list->remove(temp);
		list->print_all();
	}

	delete list;
	return 0;
}
