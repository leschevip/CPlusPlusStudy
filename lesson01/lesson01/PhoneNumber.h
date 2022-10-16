#pragma once
#include <iostream>
#include <string>
#include <optional>
#include <tuple>

using namespace std;
using PersonPhone = tuple<int, int, wstring, optional<int>>;

class PhoneNumber
{
private:
	PersonPhone _data;
public:
	PhoneNumber();

	PhoneNumber(const PhoneNumber& pn);

	PhoneNumber(int countryCode, int cityCode, wstring number, optional<int> addcode);

	friend wostream& operator << (wostream& out, const PhoneNumber& p);

	friend bool operator == (const PhoneNumber& v1, const PhoneNumber& v2);

	friend bool operator < (const PhoneNumber& v1, const PhoneNumber& v2);

	void SetCountryCode(int code);

	void SetCityCode(int code);

	void SetNumber(wstring number);

	void SetAddCode(optional<int> code);

	PersonPhone& GetFullPhone();
};