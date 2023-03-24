#pragma once

#include <vector>
#include <tuple>
#include <utility>
#include <string>
#include <map>

#include "section.h"

using namespace std;

class Course {
	// Course class for storing info on courses and their sections
	public:
		/**
		 * Constructor that takes in the name
		 * 
		 * @param course_name	String of the course name
		 */
		Course(string course_name);


		/**
		 * Function that adds a section to the private vector
		 *
		 * @param section	Section object that contains section info
		 */
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
		
		/**
		 * Map of the pre-requisite/concurrent courses
		*/
		map<Course, string> requisite_; // better name needed.
};