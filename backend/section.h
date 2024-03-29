#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Day {
        char name;
        string start_time;
        string end_time;
        friend std::ostream& operator<<(std::ostream& os, const Day& day) {
        os << "Name: " << day.name << ", Start Time: " << day.start_time
           << ", End Time: " << day.end_time;
        return os;
    }
    };

class Section {
	// Section class for storing info on times and locations


        public:
        /**
         * Constructor that takes the name of the section and its parent course
         * 
         * @param section_name          String of the section's name
         * @param section_type          String of the section's type
         * @param crn                   String of the section's crn
         * @param parent_course         String of the parent course name
         * @param d                     Day of the section
         */
        Section(string section_name, string section_type, int crn, string parent_course, vector<Day> days, string locaiton);

        /**
         * Function to get the name of the section
         * 
         * @return      string containting the section name
         */
        string getName() const;

        /**
         * Function to get a vector containing all of the section days
         * 
         * @return      string containting the section name
         */
        vector<Day> getDays() const;

        /**
         * Function to get the name of the parent course
         * 
         * @return      string containting the parent course name
         */
        string getParentCourse() const;

        /**
         * Function to get the crn of the section
         * @return int holding the crn
        */
        int getCRN() const;

        /**
         * function to get the location for the secion
         * @return string with location
        */
        string getLocation() const;

        /**
         * function to get the type of the secion
         * @return string with secion type
        */
        string getType() const;


        /**
         * Overloaded operator< for std::next_permutation
         * @param Section other section with day info
         * @return bool true if this parent course is less than the other parent course
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
        * String contain the type of section
	* Laboratory/Discussion/Lecture/...
	*/
	string type_;

        /**
	* String contain the location of the class
	* Possibly used for calculating distance between two sections' location
	*/
        string location_;
};
