#pragma once

#include "Person.h"

using namespace std;

class Student : public Person
{
private:
	int studyYear;
	static int counter;

public:

	Student(const string& name, const int& age, const Gender& gender, const float& weight, const int& studyYear)
		: Person(name, age, gender, weight)
	{
		this->studyYear = studyYear;
		counter++;
	}

	~Student()
	{
		Student::counter--;
	}

	void setStudyDuration(int studyYear)
	{
		this->studyYear = studyYear;
	}

	void print()
	{
		Person::print();

		cout << "studyYear = " << this->studyYear << "\n"
			<<  "counter   = " << Student::counter << "\n";
	}
};