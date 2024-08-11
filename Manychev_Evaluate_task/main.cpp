#include "source/think_cell_task.cpp"

#include <string>
#include <iostream>
#include <conio.h>
#include <windows.h>

int main()
{
	// instance of interval_map class
	interval_map<int, char> m('A');
	// calling of assign() function  
	m.assign(1, 3, 'B');
	return 0;
}