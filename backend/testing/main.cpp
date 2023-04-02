#include <iostream>
#include <string>
#include "json_parser.cpp"
#include "json_parser.h"
#include "course.h"
#include "section.h"
#include "schedule_maker.h"


// Example from running ./main
// Duplicate schedules show up for print testing only, will be fixed when actually generating schedules.
// Duplicates happen with the permutation checking and the currently limitied # of courses + sections.
// 
// ======== SCHEDULE ========
// CS225: AL1
//   monday: 11:00 to 11:50
//   wednesday: 11:00 to 11:50
//   friday: 11:00 to 11:50
// CS222: SDL
//   wednesday: 13:00 to 13:50
// TEMP101: SDT
//   wednesday: 15:00 to 15:50
// ==========================
// ======== SCHEDULE ========
// CS225: AL1
//   monday: 11:00 to 11:50
//   wednesday: 11:00 to 11:50
//   friday: 11:00 to 11:50
// TEMP101: SDT
//   wednesday: 15:00 to 15:50
// CS222: SDL
//   wednesday: 13:00 to 13:50
// ==========================
// ======== SCHEDULE ========
// CS225: AL1
//   monday: 11:00 to 11:50
//   wednesday: 11:00 to 11:50
//   friday: 11:00 to 11:50
// TEMP101: SDT
//   wednesday: 15:00 to 15:50
// CS222: SDL
//   wednesday: 13:00 to 13:50
// ==========================
// ======== SCHEDULE ========
// CS225: AL1
//   monday: 11:00 to 11:50
//   wednesday: 11:00 to 11:50
//   friday: 11:00 to 11:50
// TEMP101: SDT
//   wednesday: 15:00 to 15:50
// CS222: SDL
//   wednesday: 13:00 to 13:50
// ==========================
// ======== SCHEDULE ========
// TEMP101: SDT
//   wednesday: 15:00 to 15:50
// CS222: SDL
//   wednesday: 13:00 to 13:50
// CS225: AL2
//   monday: 11:00 to 11:50
//   wednesday: 11:00 to 11:50
//   friday: 11:00 to 11:50
// ==========================
// ======== SCHEDULE ========
// TEMP101: SDT
//   wednesday: 15:00 to 15:50
// CS225: AL1
//   monday: 11:00 to 11:50
//   wednesday: 11:00 to 11:50
//   friday: 11:00 to 11:50
// CS222: SDL
//   wednesday: 13:00 to 13:50
// ==========================
// ======== SCHEDULE ========
// TEMP101: SDT
//   wednesday: 15:00 to 15:50
// CS225: AL1
//   monday: 11:00 to 11:50
//   wednesday: 11:00 to 11:50
//   friday: 11:00 to 11:50
// CS222: SDL
//   wednesday: 13:00 to 13:50
// ==========================
// Number of Required Courses: 3
// Number of Courses: 3
// Number of Sections: 4



int main() {
	// Parse the json file with course info and print out possible schedules
	read_courses("example/required.json", "example/all_course.json");

	// Print out the stats of how many courses/sections were read
	read_stats();

	write_courses("example/output.json");
	
	write_courses_individual("example/outputs/out");

	return 0;
}
