#ifndef DAY_H
#define DAY_H

#include "Staff.h"
#include "Student.h"
#include <iostream>
#include <vector>

bool isOdd(short dayNumber_);

void updateStatus(std::vector<Professor>& professors_, std::vector<Academic>& academics_, std::vector<Student>& classroom_);	//displays full information about the simulation during the current day

void getLectures(std::vector<Professor>& professors_, std::vector<Student>& students_, short dayNumber_, bool isOdd_);			//searches thru professors to figure out which Lectures happen on that day
void getExercises(std::vector<Academic>& academics_, std::vector<Student>& students_, short dayNumber_, bool isOdd_);											//searches thru academics to figure out which exercises happen on that day

#endif
