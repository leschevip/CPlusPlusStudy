#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>
#include <vector>
#include <algorithm>
#include <functional>
#include "Person.h"
#include "PhoneNumber.h"

using namespace std;
using BookItem = pair<Person*, PhoneNumber*>;
using PhoneNumberResponse = tuple <wstring, optional<const PhoneNumber*>>;

class PhoneBook
{
private:
	vector<BookItem> _book;
	void read(wifstream& f, wchar_t delimeter);
	

public:
	friend wostream& operator << (wostream& out, const PhoneBook& b);

	PhoneBook(wifstream& f, wchar_t delimeter);
	
	~PhoneBook();

	void SortByName();

	void SortByPhone();

	PhoneNumberResponse GetPhoneNumber(wstring surname);

	void ChangePhoneNumber(Person p, const PhoneNumber& pn);
};