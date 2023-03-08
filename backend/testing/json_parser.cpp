#include "json_parser.h"

#include "course.cpp"
#include "section.cpp"


using json = nlohmann::json;

void read_courses(string filename) {
    // Read the json file
	std::ifstream f("test.json");
	json data = json::parse(f);

	// Read each object from the courses array
	auto coursesArr = data.at("all_courses_sections").at("courses");
	
	// Read from the required courses array
	auto requiredCoursesArr = data.at("all_courses_sections").at("required_courses");

	// std::cout << "Required Courses: " << std::endl;
	for (auto requiredCourse : requiredCoursesArr) {
		// std::cout << "  " << requiredCourse.at("course") << std::endl;
        required_courses_.push_back(string(requiredCourse.at("course")));
	}


	// Create course/section objects
	// std::cout << "-------------------" << std::endl;
	for (auto course : coursesArr) {
		// std::cout << "Course: " << course.at("name") << std::endl;

        Course c(string(course.at("name")));

		auto sectionsArr = course.at("sections");
		for (auto section : sectionsArr) {
			// std::cout << "  Section: " << section.at("section") << std::endl;

            Section s(string(section.at("section")), string(course.at("name")));

			auto days = section.at("days");
			for (auto day : days) {
				// std::cout << "    Day: " << day.at("day") << std::endl;
				// std::cout << "      Start Time: " << day.at("start_time") << std::endl;
				// std::cout << "      End Time: " << day.at("end_time") << std::endl;

                Day d;

                d.name = string(day.at("day"));
                d.start_time = string(day.at("start_time"));
                d.end_time = string(day.at("end_time"));

                s.addDay(d);
			}
            c.addSection(s);
            all_sections_.push_back(s);
		}

        courses_.push_back(c);
		
        // std::cout << "-------------------" << std::endl;
    }
}


void read_stats() {
    std::cout << "Number of Required Courses: " << required_courses_.size() << std::endl;
    std::cout << "Number of Courses: " << courses_.size() << std::endl;
    std::cout << "Number of Sections: " << all_sections_.size() << std::endl;
}