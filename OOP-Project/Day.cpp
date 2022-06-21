#include "Day.h"
#include "Staff.h"
#include "Student.h"
#include <iostream>
#include <vector>
#include <math.h>

bool isEven(short dayNumber_)
{
	return floor((dayNumber_ / 7) % 2);				//check if week is odd
}

/*
function here so that we can understand if the student is going to attend the school today
if yes, go thru todays activities (getLectures, getExercises)
otherwise, reduce fatigue
*/

void getLectures(std::vector<Professor>& professors_, std::vector<Student>& classroom_, short dayNumber_, bool isEven_, short semesterNumber_, std::vector<short>& simulationParameters_)			//searches thru professors to figure out which Lectures happen on that day
{
	short weekDay_ = dayNumber_ % 7;

	if(dayNumber_ < 112)
	{
		for (short i = 0; i < professors_.size(); i++)
		{
			if (professors_[i].lecture.showDay() == weekDay_)
			{
				//there is a lecture from professor i on this day (without odd/even)
				if (!((professors_[i].lecture.showOccurence() == 'O' && isEven_) || (professors_[i].lecture.showOccurence() == 'E' && !isEven_)))				//checking the situations when we don't have a lecture (6 combinations, 2 times where we don't)
				{
					professors_[i].lecture.updateCurrLesson();
					/*
					there is a lecture from professor i on this day (WITH odd/even)
					give student exp if attending the lecture
					*/
					for (short j = 0; j < classroom_.size(); j++)
					{
						if (classroom_[j].showStudying())			//checking if student is still studying 
						{
							if (classroom_[j].showFatigue() < 89)
							{
								classroom_[j].updateFatigue(simulationParameters_[6]);
								classroom_[j].updateKnowledge(professors_[i].lecture.showKnowledgeToGain());
							}
							else						//maybe pow(-1,classroom_[j].showFatigue()/90) is faster than if check?
							{
								classroom_[j].updateFatigue(simulationParameters_[7]);
								classroom_[j].updateKnowledge(-(professors_[i].lecture.showKnowledgeToGain()));
							}
						}						
					}
				}
			}
		}
	}
	else if (dayNumber_ == 112)									//if day 106, go thru exams,	seems to be working fine
	{
		double examVariable = (14 + 8 * semesterNumber_ - pow(static_cast<double>(semesterNumber_), 2))/(7 * static_cast<double>(semesterNumber_));			//for exam function (difficulty with semsters)
		double examVariablePow = 0;																															//for pow funct. later

		for (short i = 0; i < professors_.size(); i++)
		{
			if (professors_[i].lecture.showLExamCheck())		//does the professor have an exam
			{
				if (examVariable > 1)	examVariablePow = 1 - (static_cast<double>(professors_[i].showCourseDifficulty()) / static_cast<double>(100));			//making sure formula works (at 0.5 point it misbehaves without change)
				else	examVariablePow = static_cast<double>(professors_[i].showCourseDifficulty()) / static_cast<double>(100);

				for (short j = 0; j < classroom_.size(); j++)	//go thru exam for each student
				{
					if (classroom_[j].showStudying())
					{
						double eqVar = examVariable * static_cast<double>(classroom_[j].showKnowledge()) / 100 * 7 / static_cast<double>(semesterNumber_);			//if failed exam, end of simulation for that person

						if (!(eqVar > 1))				//if eqVar is above 1, the student has more knowledge than max required for this semester aka automatic pass
						{
							if (eqVar == 0)	classroom_[j].updateStudying();
							if ((1 / (1 + pow(((1 - (eqVar / examVariable)) / eqVar), examVariablePow))) < 0.5000)	classroom_[j].updateStudying();
						}
					}
				}
			}			
		}
	}
}

void getExercises(std::vector<Academic>& academics_, std::vector<Student>& classroom_, short dayNumber_, bool isEven_, short semesterNumber_, std::vector<short>& simulationParameters_)						//searches thru academics to figure out which exercises happen on that day
{
	short weekDay_ = dayNumber_ % 7;
	bool test = 0;

	for (short i = 0; i < academics_.size(); i++)
	{
		if (academics_[i].exercise.showDay() == weekDay_)
		{
			//there is an exercise with the academic on this day (without odd/even)
			if (!((academics_[i].exercise.showOccurence() == 'O' && isEven_) || (academics_[i].exercise.showOccurence() == 'E' && !isEven_)))
			{
				academics_[i].exercise.updateCurrLesson();
				/*
				there is a lecture from professor i on this day (WITH odd/even)
				give student exp if attending the lecture
				*/
				if (dayNumber_ > 6 && academics_[i].exercise.showETestAmount() > 0)
				{
					if (academics_[i].exercise.showOccurence() == 'O')
					{
						if ((dayNumber_ % ((112 / academics_[i].exercise.showETestAmount()) - 7)) < 13)		test = 1;	//test present
					}
					else
					{
						if ((dayNumber_ % ((112 / academics_[i].exercise.showETestAmount()) - 7)) < 6)		test = 1;	//for B & E
					}
				}
				for (short j = 0; j < classroom_.size(); j++)
				{
					if (classroom_[j].showStudying())
					{
						if (test)
						{
							if (classroom_[j].showKnowledge() < (7 * semesterNumber_ / academics_[i].exercise.showETestAmount() * floor(dayNumber_ / (112 / academics_[i].exercise.showETestAmount() - 7)))) classroom_[j].updateStudying();
						}

						if (classroom_[j].showFatigue() < 89)
						{
							classroom_[j].updateFatigue(simulationParameters_[8]);
							classroom_[j].updateKnowledge(academics_[i].exercise.showKnowledgeToGain());
						}
						else
						{
							classroom_[j].updateFatigue(simulationParameters_[9]);
							classroom_[j].updateKnowledge(-(academics_[i].exercise.showKnowledgeToGain()));
						}
					}
				}
				test = 0;
			}
		}
	}
}

void Day(std::vector<Professor>& professors_, std::vector<Academic>& academics_, std::vector<Student>& classroom_, short dayNumber_, bool isEven_, short semesterNumber_, std::vector<short>& simulationParameters_)
{
	getLectures(professors_, classroom_, dayNumber_, isEven_, semesterNumber_, simulationParameters_);
	getExercises(academics_, classroom_, dayNumber_, isEven_, semesterNumber_, simulationParameters_);
}