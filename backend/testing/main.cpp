#include <iostream>
#include "schedule.cpp"
#include "class.cpp"

#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


int main() {
	// Read the json file
	std::ifstream f("test.json");
	json data = json::parse(f);

	// Read each object from the classes array
	auto courses = data.at("all_courses_sections").at("courses");

	// For each class print the names
	for (auto course : courses) {
		std::cout << course.at("course").at("name") << std::endl;
	}

	//std::cout << data.at("all_classes_sections").at("classes") << "\n" << std::endl;

	return 0;
}
