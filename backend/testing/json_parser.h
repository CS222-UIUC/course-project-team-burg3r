#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "course.h"
#include "section.h"

using namespace std;

// Functions to read course json info and make course objects, and to read schedule objects and output schedule json info

void read_courses(string filename);

void read_stats();

vector<Course> courses_;
vector<string> required_courses_;
vector<Section> all_sections_;