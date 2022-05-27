#ifndef SAVE_H
#define SAVE_H

#include <string>
#include <vector>
#include "Professor.h"
#include "Student.h"

void getFromFile(std::string filename, std::vector<Professor>& professors_, std::vector<Academic>& academic_, std::vector<Student>& students_);

#endif