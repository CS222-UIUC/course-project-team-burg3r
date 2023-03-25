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

  // Iterate through the JSON array and populate the map
  for (auto &course : required_json["required_courses"]) {
    std::string course_name = course["course"].get<std::string>();
    std::vector<std::string> course_types =
        course["types"].get<std::vector<std::string>>();
    num_sections_ += course_types.size();
    required_courses_[course_name] = course_types;
  }

  // Print the map
  for (auto &course : required_courses_) {
    std::cout << "Required Course: " << course.first << " (";
    for (auto &type : course.second) {
      std::cout << type << ", ";
    }
    std::cout << ")" << std::endl;
  }

  std::cout << "===================" << std::endl;

  // Iterate through the JSON array and populate the Course and Section objects
  for (auto &course : course_json["courses"]) {
    std::string course_name = course["courseCode"].get<std::string>();
    Course c(course_name);

    for (auto &section : course["sections"]) {
      std::string section_name = section["section"].get<std::string>();
      std::string section_type = section["type"].get<std::string>();
      int section_crn = std::stoi(section["crn"].get<std::string>());
      std::vector<Day> days;
      for (char x : section["day"].get<std::string>()) {
        Day d = {x, section["startTime"], section["endTime"]};
        days.push_back(d);
      }

      Section s(section_name, section_type, section_crn, course_name, days);

      c.addSection(s);
    }

    courses_.push_back(c);
  }

  // Print the Course and Section objects
  for (auto &course : courses_) {
    std::cout << "Course: " << course.getName() << std::endl;
    for (auto &section : course.getSection()) {
      std::cout << "  Section: " << section.getName()
                << ", Type: " << section.getType() << std::endl;
      for (auto &day : section.getDays()) {
        std::cout << "    Day: " << day.name << std::endl;
        std::cout << "      Start Time: " << day.start_time << std::endl;
        std::cout << "      End Time: " << day.end_time << std::endl;
      }
    }
  }

  // add all possible sections into
  for (auto course : courses_) {
    for (auto section : course.getSection()) {
      all_sections_.push_back(section);
    }
  }

  std::vector<Schedule> ret = make_schedule(all_sections_, required_courses_, num_sections_);
  for (const Schedule& r : ret) {
    std::cout << r << std::endl;
  }
  std::cout << "Number of Schedules generated: " << ret.size()
            << std::endl;
}

void read_stats() {
  std::cout << "Number of Required Courses: " << required_courses_.size()
            << std::endl;
  // std::cout << "Number of Required Sections: " <<
  std::cout << "Number of Courses: " << courses_.size() << std::endl;
  std::cout << "Number of Sections needed: " << num_sections_ << std::endl;
}