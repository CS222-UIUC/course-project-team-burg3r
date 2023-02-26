#pragma once

#include <vector>
#include <tuple>
#include <utility>
#include <string>

using namespace std;

class Course {
	// Course class for storing info on courses and their sections
	public:
		/**
		 * Constructor that takes in the name and sections
		 */
		Course(string course_name, vector<pair<string, vector<tuple<string, string, string>>>> sections);

	private:
		/**
		 * String containing the class name
		 */
		string course_name_;

		/**
		 * Vector that contains all sections and their info.
		 *
		 * Pair holds the string containing section name and vector of days
		 *
		 * Tuple that contains day, start time, end time
		 */
		vector<pair<string, vector<tuple<string, string, string>>>> sections_;

};
