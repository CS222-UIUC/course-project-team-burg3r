#include "course.h"
#include "json_parser.cpp"
#include "json_parser.h"
#include "schedule_maker.h"
#include "section.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <input_file>"
              << " <time_stamp>" << std::endl;
    return 1;
  }

  // Parse the json file with course info and required courses
  read_courses(argv[1], "example/demo/all_course.json");

  // Print out the stats of how many courses/sections were read
  read_stats();

  std::string time_stamp = argv[2];
  std::string output = "example/demo/output-" + time_stamp + ".json";
  // Output one json holding all schedules
  write_courses(output);

  // Output one json for every schedule
  write_courses_individual("example/demo/outputs/out");

  return 0;
}
