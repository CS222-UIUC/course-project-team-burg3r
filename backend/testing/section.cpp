#include "section.h"

using namespace std;


Section::Section(string name, string parent_course) {
    name_ = name;
    parent_course_ = parent_course;
}

void Section::addDay(Day day) {
    days_.push_back(day);
}

string Section::getName() {
    return name_;
}

string Section::getParentCourse() {
    return parent_course_;
}

vector<Day> Section::getDays() {
    return days_;
}