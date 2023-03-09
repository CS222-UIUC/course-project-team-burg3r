#include <iostream>
#include "json_parser.cpp"
#include "json_parser.h"
#include "course.h"
#include "section.h"


int main() {
	// Parse the json file with course info
	read_courses("test.json");

	// Print out the stats of how many courses/sections were read
	read_stats();
	return 0;
}
