#pragma once

#include <iostream>
using namespace std;

class Date
{
private:
	int day;
	int month;
	int year;
public:
	Date(int y, int m, int d) : day(d), month(m), year(y)
	{

	}

	int GetDay()
	{
		return day;
	}

	int GetMonth()
	{
		return month;
	}

	int GetYear()
	{
		return year;
	}

	friend ostream& operator << (ostream& in, Date date)
	{
		int v = date.GetMonth();
		cout << date.GetYear() << "-" << (v < 10 ? "0" : "") << v;
		v = date.GetDay();
		cout << "-" << (v < 10 ? "0" : "") << v;
		return in;
	}

	friend bool operator <= (Date& l, Date& r)
	{
		if (l.year == r.year && l.month == r.month && l.day == r.day)
			return true;
		else
			return (l.year < r.year) ||
				   (l.year == r.year && l.month < r.month) ||
				   (l.year == r.year && l.month == r.month && l.day < r.day);
	}

	friend bool operator >= (Date& l, Date& r)
	{
		if (l.year == r.year && l.month == r.month && l.day == r.day)
			return true;
		else
			return (l.year > r.year) ||
			(l.year == r.year && l.month > r.month) ||
			(l.year == r.year && l.month == r.month && l.day > r.day);
	}

	friend bool operator == (Date& l, Date& r)
	{
		return l.year == r.year && l.month == r.month && l.day == r.day;
	}

	friend bool operator < (Date& l, Date& r)
	{
		return !(l >= r);
	}

	friend bool operator > (Date& l, Date& r)
	{
		return !(l <= r);
	}

};

shared_ptr<Date>& maxDate(shared_ptr<Date>& dl, shared_ptr<Date>& dr)
{
	return (*dl.get() < *dr.get() ? dr : dl);
}

void swapDates(shared_ptr<Date>& dl, shared_ptr<Date>& dr)
{
	dl.swap(dr);
}