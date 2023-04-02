#include "section.h"

using namespace std;


Section::Section(string section_name, string section_type, int crn, string parent_course, vector<Day> days, string location)
    : name_(section_name), type_(section_type), crn_(crn), parent_course_(parent_course), days_(days), location_(location)  {}

string Section::getName() const {
    return name_;
}

string Section::getParentCourse() const {
    return parent_course_;
}

vector<Day> Section::getDays() const {
    return days_;
}

int Section::getCRN() const {
    return crn_;
}

string Section::getType() const {
    return type_;
}

string Section::getLocation() const {
    return location_;
}