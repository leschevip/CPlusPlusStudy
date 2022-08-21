#pragma once

#include <iostream>
#include <string>
#include "Gender.h"
#include "Helper.h"

using namespace std;

class Person
{

protected:
	string name;
	int age;
	Gender gender;
	float weight;

public:

	Person(const string& name, const int& age, const Gender& gender, const float& weight)
		: name(name), age(age), gender(gender), weight(weight)
	{

	}

	void setName(const string& name)
	{
		this->name = name;
	}

	void setAge(const int& age)
	{
		this->age = age;
	}

	void setWeight(const float& weight)
	{
		this->weight = weight;
	}

	void print()
	{
		cout << "Person info:\n"
			<< "name   = " << this->name << "\n"
			<< "age    = " << this->age << "\n"
			<< "gender = " << genderToString(this->gender) << "\n"
			<< "weight = " << this->weight << "\n";
	}
};