#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "course.h"
#include "section.h"

#include "schedule_maker.cpp"
#include "schedule_maker.h"

using namespace std;

// Functions to read course json info and make course objects, and to read schedule objects and output schedule json info


/**
 * Function to parse the course and section information
 * 
 * @param      string String containing the name and path of the json file
 */
void read_courses(string filename);


/**
 * Function to print the number of courses and sections parsed
 */
void read_stats();

/**
 * Vector holding all of the Courses parsed
 */
vector<Course> courses_;

/**
 * Vector holding strings with names of all required classes.
 * This is important to make sure a schedule contains all required courses at a minimum.
 */
vector<string> required_courses_;

/**
 * Vector holding every section that was parsed. This is useful for schedule generation
 * as we can build schedules using every section stored.
 */
vector<Section> all_sections_;