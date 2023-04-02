#pragma once

#include <mutex>
#include <string>
#include <thread>
#include <vector>

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
 * @param map<string, vector<string>> map of required courses and required
 * section types?
 * @param int number of sections needed for the schedule to be complete
 * @param string string containing the preferred start time for all courses and
 * sections
 * @param string string containing the preferred end time for all courses and
 * sections
 */
std::vector<Schedule> make_schedule(
    std::vector<Section> all_sections,
    std::map<std::string, std::vector<std::string>> required_courses_,
    int num_sections_, std::string preferred_start_time,
    std::string preferred_end_time, std::string preferred_padding);

/**
 * Experimental multi-thread support
 * Not working yet bcuz the (schedule.size() == num_sections_) might not be true
 * for most of the time since each sub-thread only works on part of the
 * sections. So if there's no way to fix this, we might just drop support for
 * multithread?
 *
 * References:
 * https://www.bogotobogo.com/cplusplus/multithreading_pthread.php
 * https://en.cppreference.com/w/cpp/thread/unique_lock
 * https://en.cppreference.com/w/cpp/thread/mutex
 * https://en.cppreference.com/w/cpp/thread/thread
 * https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
 * https://stackoverflow.com/questions/14709233/how-to-use-create-unique-lock-in-c
 */
void worker(std::vector<Section> all_sections,
            std::map<std::string, std::vector<std::string>> required_courses_,
            int num_sections_, std::string preferred_start_time,
            std::string preferred_end_time, std::string preferred_padding,
            std::vector<Schedule> &ret, std::mutex &ret_mutex);

/**
 * Helper function for time_conflict function.
 * Calculates the time difference in minutes to help satisfy user's padding
 * requirement.
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
bool time_conflict(std::string start_one, std::string end_one,
                   std::string start_two, std::string end_two,
                   std::string preferred_padding);