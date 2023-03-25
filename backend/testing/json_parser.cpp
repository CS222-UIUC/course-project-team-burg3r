#include "json_parser.h"

#include "course.cpp"
#include "section.cpp"

using json = nlohmann::json;

void read_courses(string filename) {
  // Read the json file
  std::ifstream required("required.json");
  std::ifstream course("all_course.json");
  json required_json = json::parse(required);
  json course_json = json::parse(course);

  // Read each object from the courses array
  auto coursesArr = course_json.at("courses");

  std::map<std::string, std::vector<std::string>> required_courses;

  // Iterate through the JSON array and populate the map
  for (auto &course : required_json["required_courses"]) {
    std::string course_name = course["course"].get<std::string>();
    std::vector<std::string> course_types =
        course["types"].get<std::vector<std::string>>();
    required_courses[course_name] = course_types;
  }

  // Print the map
  for (auto &course : required_courses) {
    std::cout << "Course: " << course.first << std::endl;
    std::cout << "Types: ";
    for (auto &type : course.second) {
      std::cout << type << ", ";
    }
    std::cout << std::endl;
  }

  // Iterate through the JSON array and populate the Course and Section objects
  for (auto &course : course_json["courses"]) {
    std::string course_name = course["courseCode"].get<std::string>();
    Course c(course_name);

    for (auto &section : course["sections"]) {
      std::string section_name = section["section"].get<std::string>();
      Section s(section_name, course_name);

      for (auto &day : section["days"]) {
        Day d;
        // M,T,W,R,F
        d.name = day["day"].get<std::string>();
        d.start_time = day["startTime"].get<std::string>();
        d.end_time = day["endTime"].get<std::string>();
        s.addDay(d);
      }

      c.addSection(s);
    }

    courses_.push_back(c);
  }

  // Print the Course and Section objects
  for (auto &course : courses_) {
    std::cout << "Course: " << course.getName() << std::endl;
    for (auto &section : course.getSection()) {
      std::cout << "  Section: " << section.getName() << std::endl;
      for (auto &day : section.getDays()) {
        std::cout << "    Day: " << day.name << std::endl;
        std::cout << "      Start Time: " << day.start_time << std::endl;
        std::cout << "      End Time: " << day.end_time << std::endl;
      }
    }
  }

  make_schedule(all_sections_);
}

void read_stats() {
  std::cout << "Number of Required Courses: " << required_courses_.size()
            << std::endl;
  std::cout << "Number of Courses: " << courses_.size() << std::endl;
  std::cout << "Number of Sections: " << all_sections_.size() << std::endl;
}