#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct Day {
        string name;
        string start_time;
        string end_time;
    };

class Section {
	// Section class for storing info on times and locations


	public:
        Section(string name, string parent_course);

        void addDay(Day day);

        string getName();
        vector<Day> getDays();
        string getParentCourse();

	private:
        string name_;
        string parent_course_;
        vector<Day> days_;
};
