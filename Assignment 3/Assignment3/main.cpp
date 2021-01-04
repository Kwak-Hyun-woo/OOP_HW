////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 3: Source file - Main Function for Testing
// YOU WILL NOT submit this file. Again, DO NOT submit.
// Use it for your testing
////////////////////////////////////////////////////////////////////////////////
#include "hw3.h"

#include <iostream>

void testcase(Ordered* o) {
	o->add(30);
	o->add(20);
	o->add(20);
	o->add(10);
	o->add(15);
	o->add(15);
	o->add(25);

	int vals[] = { 10, 20, 35, 35, 10 };
	o->add(vals, sizeof(vals) / sizeof(int));

	o->remove(2);

	for (int i = 0; i < o->size(); ++i) {
		std::cout << (*o)[i] << ", ";
	}
	std::cout << std::endl;

	std::cout << std::boolalpha << (*o >> 15) << std::endl;
	std::cout << std::boolalpha << (*o >> 40) << std::endl;
}

int main()
{
	Ordered orderedList;
	testcase(&orderedList);

	// Remove "//" below after implementing OrderedSet
	OrderedSet orderedSet;
	testcase(&orderedSet);


	return 0;
}