#pragma once

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
 * helper function checking if there's any time conflict
 * @todo compare if there's a time conflict
 * need to consider exact section
 */
bool time_conflict();