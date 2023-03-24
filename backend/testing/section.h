#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct Day {
        string name;
        string start_time;
        string end_time;
        // maybe we can change this into military time format.
        // so start_time and end_time can be integers.
        // better when checking if there's a conflict in time.
    };

class Section {
	// Section class for storing info on times and locations


        public:
        /**
         * Constructor that takes the name of the section and its parent course
         * 
         * @param name          String of the section name
         * @param parent_course String of the parent course name
         */
        Section(string name, string parent_course);


        /**
         * Function to add a Day struct to the private vector
         * 
         * @param day   Day struct containing name and times
         */
        void addDay(Day day);

        /**
         * Function to get the name of the section
         * 
         * @return      string containting the section name
         */
        string getName();

        /**
         * Function to get a vector containing all of the section days
         * 
         * @return      string containting the section name
         */
        vector<Day> getDays();

        /**
         * Function to get the name of the parent course
         * 
         * @return      string containting the parent course name
         */
        string getParentCourse();

        /**
         * Function to get the crn of the course
        */
        int getCRN() const;

        /**
         * function to get the location for the course
        */
        string getLocation() const;

        /**
         * function to get the type of the course
        */
        string getType() const;


        /**
         * Overloaded operator< for std::next_permutation
        */
        bool operator<(Section other) {
                return parent_course_ < other.parent_course_;
        }

	private:

        /**
	* int that contains the CRN
	*/
	int crn_;


        /**
         * String that holds the name of the section
         */
        string name_;

        /**
         * String that holds the name of the parent course. Useful for comparing whether two sections
         * should exist on the same schedule. IE, two sections for the same course should not be.
         */
        string parent_course_;

        /**
         * Vector that contains all of the section days and times
         */
        vector<Day> days_;

        /**
        * String contain the type of course
	* Laboratory/Discussion/Lecture/...
	*/
	string type_;

        /**
	* String contain the location of the class
	* Possibly used for calculating distance between two courses' location
	*/
	string location_;
};
