#include <iostream>
#include "json_parser.cpp"
#include "json_parser.h"
#include "course.h"
#include "section.h"

// Example print out from running ./main
//
// Required Courses:
//   "CS225"
//   "CS222"
// -------------------
// Course: "CS225"
//   Section: "AL1"
//     Day: "monday"
//       Start Time: "1100"
//       End Time: "1150"
//     Day: "wednesday"
//       Start Time: "1100"
//       End Time: "1150"
//     Day: "friday"
//       Start Time: "1100"
//       End Time: "1150"
//   Section: "AL2"
//     Day: "monday"
//       Start Time: "1100"
//       End Time: "1150"
//     Day: "wednesday"
//       Start Time: "1100"
//       End Time: "1150"
//     Day: "friday"
//       Start Time: "1100"
//       End Time: "1150"
// -------------------
// Course: "CS222"
//   Section: "SDL"
//     Day: "wednesday"
//       Start Time: "1300"
//       End Time: "1350"
// -------------------

int main() {
	// Parse the json file with course info
	read_courses("test.json");

	// Print out the stats of how many courses/sections were read
	read_stats();
	return 0;
}
