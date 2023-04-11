#include "course.h"

Course::Course(string course_name) {
    course_name_ = course_name;
}

void Course::addSection(Section section) {
    sections_.push_back(section);
}