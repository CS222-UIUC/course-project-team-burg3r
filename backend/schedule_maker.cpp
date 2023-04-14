#include "schedule_maker.h"

#include <algorithm>
#include <iostream>

std::vector<Schedule>
make_schedule(std::vector<Section> all_sections,
              std::map<std::string, std::vector<std::string>> required_courses_,
              int num_sections_, std::string preferred_start_time,
              std::string preferred_end_time, std::string preferred_padding, std::vector<Section> blocked_times) {
  std::vector<Schedule> ret;
  std::vector<Section> schedule;
  std::vector<std::string> courses_scheduled;

  // preferred start time, probably replace with morning/afternoon preference
  // with set times
  do {
    // Reset the schedule for this iteration
    schedule.clear();
    courses_scheduled.clear();

    // Populate schedule with blocked out times
    for (Section blocked : blocked_times) {
      schedule.push_back(blocked);
    }

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
                                       section_day.start_time,
                                       section_day.end_time, preferred_padding)) {
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
    if (schedule.size() == num_sections_ + blocked_times.size()) {
      Schedule s(schedule, courses_scheduled);

      bool existed = false;
      for (Schedule &existing_schedule : ret) {
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

int time_diff_in_minutes(std::string start, std::string end) {
  int hours_start = stoi(start.substr(0, 2));
  int hours_end = stoi(end.substr(0, 2));
  int minutes_start = stoi(start.substr(3, 2));
  int minutes_end = stoi(end.substr(3, 2));
  
  int total_minutes_start = hours_start * 60 + minutes_start;
  int total_minutes_end = hours_end * 60 + minutes_end;

  return abs(total_minutes_start - total_minutes_end);
}

bool time_conflict(std::string start_one, std::string end_one,
                   std::string start_two, std::string end_two, std::string preferred_padding) {
  int padding_minutes = time_diff_in_minutes("00:00", preferred_padding);
  int end_one_minutes = time_diff_in_minutes("00:00", end_one);
  int start_two_minutes = time_diff_in_minutes("00:00", start_two);

  if (start_one <= start_two && end_one_minutes + padding_minutes >= start_two_minutes ||
      start_two <= start_one && end_two >= end_one) {
    return true;
  } else {
    return false;
  }
}