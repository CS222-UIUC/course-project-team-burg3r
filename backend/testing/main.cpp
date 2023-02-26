#include <iostream>
#include "schedule.cpp"
#include "course.cpp"
#include "json_parser.h"
#include "schedule_maker.h"

#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

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
	// Read the json file
	std::ifstream f("test.json");
	json data = json::parse(f);

	// Read each object from the courses array
	auto coursesArr = data.at("all_courses_sections").at("courses");
	
	// Read from the required courses array
	auto requiredCoursesArr = data.at("all_courses_sections").at("required_courses");

	// Print each required course name
	std::cout << "Required Courses: " << std::endl;
	for (auto requiredCourse : requiredCoursesArr) {
		std::cout << "  " << requiredCourse.at("course") << std::endl;
	}

	// For each course print the names, days, and times
	std::cout << "-------------------" << std::endl;
	for (auto course : coursesArr) {
		std::cout << "Course: " << course.at("name") << std::endl;

		auto sectionsArr = course.at("sections");
		for (auto section : sectionsArr) {
			std::cout << "  Section: " << section.at("section") << std::endl;

			auto days = section.at("days");
			for (auto day : days) {
				std::cout << "    Day: " << day.at("day") << std::endl;
				std::cout << "      Start Time: " << day.at("start_time") << std::endl;
				std::cout << "      End Time: " << day.at("end_time") << std::endl;
			}
		}
		
		std::cout << "-------------------" << std::endl;
	}

	return 0;
}
