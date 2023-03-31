#include "json_parser.h"

#include "course.cpp"
#include "section.cpp"

using json = nlohmann::json;

void read_courses(string req, string all) {
  // Read the json file
  std::ifstream required(req);
  std::ifstream course(all);
  json required_json = json::parse(required);
  json course_json = json::parse(course);

  preferred_start_time_ = required_json["preferred_start_time"];
  preferred_end_time_ = required_json["preferred_end_time"];

  // Iterate through the JSON array and populate the map
  for (auto &course : required_json["required_courses"]) {
    std::string course_name = course["course"].get<std::string>();
    std::vector<std::string> course_types =
        course["types"].get<std::vector<std::string>>();
    num_sections_ += course_types.size();
    required_courses_[course_name] = course_types;
  }

  // Print the map
  // for (auto &course : required_courses_) {
  //   std::cout << "Required Course: " << course.first << " (";
  //   for (auto &type : course.second) {
  //     std::cout << type << ", ";
  //   }
  //   std::cout << ")" << std::endl;
  // }

  // std::cout << "===================" << std::endl;

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

      // this is due to a typo in the course json file.
      std::string location = section["instructor"].get<std::string>();
      Section s(section_name, section_type, section_crn, course_name, days, location);

      c.addSection(s);
    }

    courses_.push_back(c);
  }

  // Print the Course and Section objects
  // for (auto &course : courses_) {
  //   std::cout << "Course: " << course.getName() << std::endl;
  //   for (auto &section : course.getSection()) {
  //     std::cout << "  Section: " << section.getName()
  //               << ", Type: " << section.getType() << std::endl;
  //     for (auto &day : section.getDays()) {
  //       std::cout << "    Day: " << day.name << std::endl;
  //       std::cout << "      Start Time: " << day.start_time << std::endl;
  //       std::cout << "      End Time: " << day.end_time << std::endl;
  //     }
  //   }
  // }

  // add all possible sections into
  for (auto course : courses_) {
    for (auto section : course.getSection()) {
      all_sections_.push_back(section);
    }
  }

  ret_ = make_schedule(all_sections_, required_courses_, num_sections_, preferred_start_time_, preferred_end_time_);
  for (const Schedule &r : ret_) {
    std::cout << r << std::endl;
  }
}

void read_stats() {
  std::cout << "Number of Required Courses: " << required_courses_.size()
            << std::endl;
  std::cout << "Number of Courses: " << courses_.size() << std::endl;
  std::cout << "Number of Sections needed: " << num_sections_ << std::endl;
  std::cout << "Number of Schedules generated: " << ret_.size() << std::endl;
}

json parse(Schedule schedule) {
  json j;
  for (const Section &section : schedule.getSchedule()) {
    json section_json;
    section_json["course"] = section.getParentCourse();
    section_json["section"] = section.getName();
    section_json["type"] = section.getType();
    section_json["crn"] = section.getCRN();
    section_json["location"] = section.getLocation();
    section_json["days"];
    // had to convert day.name back to string, json turned char into ascii index
    for (const Day &day : section.getDays()) {
      section_json["days"].push_back(
          {{"day", std::string(1, day.name)}, {"start_time", day.start_time}, {"end_time", day.end_time}});
    }
    j["schedule"].push_back(section_json);
  }
  return j;
}

void write_courses(string output) {
  json out = json::array();
  for (const Schedule &schedule : ret_) {
    out.push_back(parse(schedule));
  }

  std::ofstream o(output);
  o << std::setw(4) << out << std::endl;
  std::cout << "Schedules generated successfully, saved to " << output << std::endl;
  o.close();
}

void write_courses_individual(string output) {
  int count = 0;
  
  for (const Schedule &schedule : ret_) {
    json out = json::array();
    out.push_back(parse(schedule));
    
    string output_modified = output;
    output_modified += "_";
    output_modified += to_string(count);
    output_modified += ".json";
    
    std::ofstream o(output_modified);
    o << std::setw(4) << out << std::endl;

    o.close();
    count++;
  }
  std::cout << "Individual Schedules generated successfully, saved to " << output << std::endl;
}