#pragma once

#include <vector>
#include <string>

#include "course.h"
#include "schedule.h"

// Functions to create possible schedules using course objects

/**
 * helper function to generate the schedule
 * @param vector<string>
 */
Schedule make_schedule(vector<string>);


/**
 * Test function to generate the schedules
 * @param vector<Section> vector of all sections from all given courses
 */
void make_schedule(std::vector<Section> all_sections);

/**
 * Schedule maker function using sections and checking for required courses
 * @param vector<Section> vector of Sections
 * @param map<string, vector<string>> map of required courses and required section types?
 * @param int number of sections needed for the schedule to be complete
 * @param string string containing the preferred start time for all courses and sections
 * @param string string containing the preferred end time for all courses and sections
 */
std::vector<Schedule> make_schedule(
    std::vector<Section> all_sections,
    std::map<std::string, std::vector<std::string>> required_courses_,
    int num_sections_, std::string preferred_start_time, std::string preferred_end_time, std::string preferred_padding);


/**
 * Helper function for time_conflict function.
 * Calculates the time difference in minutes to help satisfy user's padding requirement.
 * @param time1 start time 
 * @parem time2 end time
*/
int time_diff_in_minutes(std::string start, std::string end);

/**
 * Function to check whether section times overlap
 * @param string start time for first section
 * @param string end time for first section
 * @param string start time for second section
 * @param string end time for second section
 * @return true if conflict, false if no conflict
 */
bool time_conflict(std::string start_one, std::string end_one, std::string start_two, std::string end_two, std::string preferred_padding);