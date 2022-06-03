/*
semester - full week
7 classes per day MAX	=>			2*5*7 = 70 professors max
mod 7 = day				+			mod 2 = even/odd

professors - in table/vector
professors - max cap or not?
*/

#include <iostream>
#include <vector>
#include <conio.h>
#include <math.h>
#include "Student.h"
#include "Staff.h"
#include "Day.h"
#include "Save.h"

const short semesterLength = 105;
const short semesterAmount = 7;

std::vector<Professor> staff;										//vectors to contain Professors, Academics and Students
std::vector<Academic> academics;
std::vector<Student> classroom;

short dayNumber = 1;												//tracking days passed
bool evenWeek = 1;
short semesterNumber = 1;
short simulationNumber = 1;

int main(int argc, char* argv[])
{
	unsigned char button;

	getFromFile(argv[1], staff, academics, classroom);

	updateStatus(staff, academics, classroom);
	
	do
	{																			//after each day
		button = _getch();
		if (static_cast <int>(button) == 13)									//if enter pressed, go to thru the day
		{
			std::cout << "Day: " << dayNumber << "\n";
			getLectures(staff, classroom, dayNumber, isOdd(dayNumber));
			updateStatus(staff, academics, classroom);
			dayNumber++;
		}
	} while (static_cast <int>(button) != 27);									//ESC stops the simulation

	return 0;
}