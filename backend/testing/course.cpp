#include "course.h"

Course::Course(string course_name, vector<pair<string, vector<tuple<string, string, string>>>> sections) {
    course_name_ = course_name;
    sections_ = sections;
}