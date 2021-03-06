#ifndef DAY_H
#define DAY_H

#include "Staff.h"
#include "Student.h"
#include <iostream>
#include <vector>

bool isEven(short dayNumber_);

void getLectures(std::vector<Professor>& professors_, std::vector<Student>& classroom_, short dayNumber_, bool isOdd_, short semesterNumber_, std::vector<short>& simulationParameters_);			//searches thru professors to figure out which Lectures happen on that day
void getExercises(std::vector<Academic>& academics_, std::vector<Student>& classroom_, short dayNumber_, bool isOdd_, short semesterNumber_, std::vector<short>& simulationParameters_);											//searches thru academics to figure out which exercises happen on that day
void Day(std::vector<Professor>& professors_, std::vector<Academic>& academics_, std::vector<Student>& classroom_, short dayNumber_, bool isOdd_, short semesterNumber_, std::vector<short>& simulationParameters_);

#endif
