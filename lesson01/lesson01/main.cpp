#include <iostream>
#include <fstream>
#include <string>
#include "PhoneBook.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	Person p1(L"Лещёв", L"Иван", nullopt);
	Person p2(L"Лещёв", L"Иван", L"Павлович");

	wcout << boolalpha << p1 << " < " << p2 << ": " << (p1 < p2) << endl;
	wcout << boolalpha << p1 << " = " << p2 << ": " << (p1 == p2) << endl;

	std::locale::global(std::locale("en_US.utf8"));
	wifstream f;
	f.imbue(locale("en_EN.utf8"));
	f.open("book.txt");
	PhoneBook book(f, L';');
	wcout << book << endl;
	
	cout << "------SortByPhone-------" << endl;
	book.SortByPhone();
	wcout << book << endl;
	cout << "------SortByName--------" << endl;
	book.SortByName();
	wcout << book << endl;
	cout << "-----GetPhoneNumber-----" << endl;
	auto print_phone_number = [&book](const wstring& surname) {
		wcout << surname << "\t";
		auto response = book.GetPhoneNumber(surname);
		if (get<0>(response).empty())
			wcout << **get<1>(response);
		else
			wcout << get<0>(response);
		wcout << endl;
	};
	print_phone_number(L"Лещёв");
	print_phone_number(L"Левщенко");
	print_phone_number(L"Лещёва");
	wcout << endl;
	
	cout << "----ChangePhoneNumber----" << endl;
	book.ChangePhoneNumber(Person(L"Лещёв", L"Иван", L"Павлович"), PhoneNumber(7, 123, L"15344458", nullopt));
	book.ChangePhoneNumber(Person(L"Третьяков", L"Иван", L"Павлович"), PhoneNumber(7, 123, L"15344458", nullopt));
	wcout << book;
}