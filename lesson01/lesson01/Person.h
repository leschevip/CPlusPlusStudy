#pragma once
#include <iostream>
#include <string>
#include <optional>
#include <tuple>

using namespace std;
using PersonName = tuple<wstring, wstring, optional<wstring>>;

class Person
{
private:
	PersonName _data;
	wstring _emptyval;

public:
	Person();

	Person(wstring surname, wstring name, optional<wstring> patronymic);

	friend wostream& operator << (wostream& out, const Person& p);

	friend bool operator == (const Person& v1, const Person& v2);
	
	friend bool operator < (const Person& v1, const Person& v2);

	void SetName(wstring name);

	void SetSurname(wstring surname);

	void SetPatronymic(optional<wstring> patronymic);

	wstring& GetName();
	
	wstring& GetSurName();

	wstring& GetPatronymic();

	PersonName& GetFullName();

};