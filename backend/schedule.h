#pragma once

#include <algorithm>

#include "course.h"

class Schedule {
  // Class that holds schedule information
 public:
  /**
   * Default Constructor
   */
  Schedule(std::vector<Section> schedule,
           std::vector<std::string> courses_scheduled)
      : schedule_(schedule), courses_scheduled_(courses_scheduled) {}

  /**
   * helper functio that converts a schedule to json
   * @param output file name
   */
  void parse(string out);

  /**
   * operator overload, return true if two schedule are identical
   */
  friend bool operator==(const Schedule& lhs, const Schedule& rhs) {
    // check if they have the same schedule size, then check if the sorted crn
    // vector are identical
    if (lhs.getSchedule().size() != rhs.getSchedule().size()) return false;
    std::vector<int> l_crn, r_crn;

    for (auto section : lhs.getSchedule()) l_crn.push_back(section.getCRN());
    for (auto section : rhs.getSchedule()) r_crn.push_back(section.getCRN());
    std::sort(l_crn.begin(), l_crn.end());
    std::sort(r_crn.begin(), r_crn.end());

    for (int i = 0; i < l_crn.size(); i++) {
      if (l_crn[i] != r_crn[i]) {
        return false;
      }
    }

    return true;
  }

  /**
   * Helper functions
   */
  std::vector<Section> getSchedule() const { return schedule_; }

  std::vector<std::string> getScheduledCourse() const {
    return courses_scheduled_;
  }

  // I have no idea how to put this into schedule.cpp without causing any error
  friend std::ostream& operator<<(std::ostream& os, const Schedule& schedule) {
    os << "======== SCHEDULE ========" << std::endl;
    for (Section s : schedule.getSchedule()) {
      os << s.getParentCourse() << "; Sec " << s.getName() << "; CRN" << s.getCRN() << std::endl;
      for (Day day : s.getDays()) {
        os << "  " << day.name << ": " << day.start_time << " to "
           << day.end_time << std::endl;
      }
    }
    os << "==========================" << std::endl;
    return os;
  }

 private:
  /**
   * Vector that holds all the courses in this schedule
   */
  std::vector<Section> schedule_;
  std::vector<std::string> courses_scheduled_;
};
