#include <iostream>
#include <string>
#include "json_parser.cpp"
#include "json_parser.h"
#include "course.h"
#include "section.h"
#include "schedule_maker.h"


int main() {
	// Parse the json file with course info and required courses
	read_courses("example/required.json", "example/all_course.json");

	// Print out the stats of how many courses/sections were read
	read_stats();

	// Output one json holding all schedules
	write_courses("example/output.json");

	// Output one json for every schedule
	write_courses_individual("example/outputs/out");

	return 0;
}
