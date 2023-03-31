#include "schedule_maker.h"

#include <algorithm>
#include <iostream>

std::vector<Schedule> make_schedule(
    std::vector<Section> all_sections,
    std::map<std::string, std::vector<std::string>> required_courses_,
    int num_sections_, std::string preferred_start_time, std::string preferred_end_time) {
  std::vector<Schedule> ret;
  std::vector<Section> schedule;
  std::vector<std::string> courses_scheduled;

  // preferred start time, probably replace with morning/afternoon preference with set times
  do {
    // Reset the schedule for this iteration
    schedule.clear();
    courses_scheduled.clear();

    for (Section section : all_sections) {
      // Skip sections that are not required for any course
      if (required_courses_.count(section.getParentCourse()) == 0) {
        continue;
      }

      // Skip sections for courses that have already been scheduled
      // if (std::find(courses_scheduled.begin(), courses_scheduled.end(),
      //               section.getParentCourse()) != courses_scheduled.end()) {
      //   continue;
      // }

      if (schedule.empty()) {
          bool conflict = false;
          for (Day section_day : section.getDays()) {
            if (preferred_start_time > section_day.start_time) {
              conflict = true;
              break;
            } else if (section_day.end_time > preferred_end_time) {
              conflict = true;
              break;
            }
          }
          if (conflict) {
            continue;
          } else {
            schedule.push_back(section);
          }
      } else {
        bool conflict = false;
        for (Section scheduled_section : schedule) {
          for (Day scheduled_section_day : scheduled_section.getDays()) {
            for (Day section_day : section.getDays()) {
              if (preferred_start_time > section_day.start_time) {
                conflict = true;
                break;
              } else if (section_day.end_time > preferred_end_time) {
                conflict = true;
                break;
              } else if (time_conflict(scheduled_section_day.start_time,
                                scheduled_section_day.end_time,
                                section_day.start_time, section_day.end_time)) {
                conflict = true;
                break;
              }
            }
            if (conflict) {
              break;
            }
          }
          if (conflict) {
            break;
          }
        }

        if (!conflict) {
          bool overlap = false;
          for (Section s : schedule) {
            if (s.getParentCourse() == section.getParentCourse()) {
              // Check if a section of the same type is already scheduled
              if (s.getType() == section.getType()) {
                overlap = true;
                break;
              }
            }
          }
          if (!overlap) {
            schedule.push_back(section);
          }
        }
      }

      // if (schedule.size() == num_sections_) {
      //   break;
      // }
    }
    // Check if this schedule satisfies all required types for its course
    if (schedule.size() == num_sections_) {
      Schedule s(schedule, courses_scheduled);

      bool existed = false;
      for (Schedule& existing_schedule : ret) {
        if (existing_schedule == s) {
          // Schedule already exists, return true to indicate duplicate
          existed = true;
          continue;
        }
      }
      if (!existed) {
        // std::cout << s << std::endl;
        ret.push_back(s);
      }
    }

  } while (std::next_permutation(all_sections.begin(), all_sections.end()));

  return ret;
}

bool time_conflict(std::string start_one, std::string end_one,
                   std::string start_two, std::string end_two) {
  if (start_one <= start_two && end_one >= end_two ||
      start_two <= start_one && end_two >= end_one) {
    return true;
  } else {
    return false;
  }
}