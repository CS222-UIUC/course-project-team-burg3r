#pragma once

#include <vector>
#include <tuple>
#include <utility>
#include <string>

#include "section.h"

using namespace std;

class Course {
	// Course class for storing info on courses and their sections
	public:
		/**
		 * Constructor that takes in the name and sections
		 */
		Course(string course_name);

		void addSection(Section section);

	private:
		/**
		 * String containing the class name
		 */
		string course_name_;

		/**
		 * Vector that contains all sections and their info.
		 */
		vector<Section> sections_;

};
