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

	private:

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
};
