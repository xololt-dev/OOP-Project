#ifndef AFTERHOURS_H
#define AFTERHOURS_H

#include "Student.h"
#include <iostream>
#include <vector>

//void goParty(short &fatigue_, short &knowldege_);

bool isWeekend(short dayNumber_);

void getSleep(Student classroom_);

void goRelax(Student classroom_);
void goStudy(Student classroom_);

void goParty(Student classroom_);

void Afterhours(std::vector<Student>& classroom_, bool isWeekend_);

#endif
