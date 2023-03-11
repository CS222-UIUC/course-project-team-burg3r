#pragma once

#include "course.h"

class Schedule {
  // Class that holds schedule information
 public:
  /**
   * helper functio that converts a schedule to json
   * @param output file name
   */
  void parse(string out);

 private:
  /**
   * Vector that holds all the courses in this schedule
   */
  vector<Course> course_;
};
