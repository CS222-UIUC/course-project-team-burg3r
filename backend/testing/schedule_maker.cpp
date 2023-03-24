#include "schedule_maker.h"

#include <iostream>
#include <algorithm>


void make_schedule(std::vector<Section> all_sections) {
    
    do {
        std::vector<Section> schedule;
        for (Section section : all_sections) {
            if (schedule.empty()) {
                schedule.push_back(section);
            } else {
                bool conflict = false;
                for (Section scheduled_section : schedule) {
                    for (Day scheduled_section_day : scheduled_section.getDays()) {
                        for (Day section_day : section.getDays()) {
                            if (time_conflict(scheduled_section_day.start_time, scheduled_section_day.end_time, section_day.start_time, section_day.end_time)) {
                                // std::cout << "CONFLICT BETWEEN (" << scheduled_section_day.name << ", " << scheduled_section_day.start_time << ", " << scheduled_section_day.end_time << ")" << " AND (" << section_day.name << ", " << section_day.start_time << ", " << section_day.end_time << ")" << std::endl;
                                conflict = true;
                                break;
                            } else {
                                // std::cout << "NO CONFLICT BETWEEN (" << scheduled_section_day.name << ", " << scheduled_section_day.start_time << ", " << scheduled_section_day.end_time << ")" << " AND (" << section_day.name << ", " << section_day.start_time << ", " << section_day.end_time << ")" << std::endl;
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
                            // Ensure you can't add two different sections from the same course
                            overlap = true;
                            break;
                        }
                    }
                    if (!overlap) {
                        schedule.push_back(section);
                    }
                }
            }
        }
        std::cout << "======== SCHEDULE ========" << std::endl;
        for (Section s : schedule) {
            std::cout << s.getParentCourse() << ": " << s.getName() << std::endl;
            for (Day day : s.getDays()) {
                std::cout << "  " << day.name << ": " << day.start_time << " to " << day.end_time << std::endl;
            }
        }
        std::cout << "==========================" << std::endl;
    } while (std::next_permutation(all_sections.begin(), all_sections.end()));
}



bool time_conflict(std::string start_one, std::string end_one, std::string start_two, std::string end_two) {
    if (start_one <= start_two && end_one >= end_two || start_two <= start_one && end_two >= end_one) {
        return true;
    } else {
        return false;
    }
}