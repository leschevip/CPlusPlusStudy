#include "PhoneBook.h"

PhoneBook::PhoneBook(wifstream& f, wchar_t delimeter)
{
	read(f, delimeter);
}

PhoneBook::~PhoneBook()
{
	for (auto p : _book)
	{
		delete p.first;
		delete p.second;
	}
	_book.clear();
}

wostream& operator << (wostream& out, const PhoneBook& b)
{
	for (auto p : b._book)
	{
		out << *(p.first) << L"  " << *(p.second) << endl;
	}
	return out;
}

void PhoneBook::read(wifstream& f, wchar_t delimeter)
{
	if (f.is_open())
	{
		wstring str;
		while (getline(f, str))
		{
			wstringstream row(str);
			Person* p = new Person();
			PhoneNumber* pn = new PhoneNumber();

			wstring v;
			getline(row, v, delimeter);
			p->SetSurname(v);
			getline(row, v, delimeter);
			p->SetName(v);
			getline(row, v, delimeter);
			p->SetPatronymic(!v.empty() ? optional<wstring>(v) : nullopt);

			getline(row, v, delimeter);
			pn->SetCountryCode(stoi(v.find(L"+") ? v.substr(1) : v));
			getline(row, v, delimeter);
			pn->SetCityCode(stoi(v));
			getline(row, v, delimeter);
			pn->SetNumber(v);
			getline(row, v, delimeter);
			pn->SetAddCode(!v.empty() ? optional<int>(stoi(v)) : nullopt);

			
			_book.push_back(make_pair(p, pn));
		}
	}
}

void PhoneBook::SortByName()
{
	auto compare = [](BookItem left, BookItem right) -> bool
	{
		PersonName pl = left.first->GetFullName();
		PersonName pr = right.first->GetFullName();

		if (get<0>(pl) == get<0>(pr))
		{
			if (get<1>(pl) == get<1>(pr))
			{
				if (get<2>(pl) == get<2>(pr))
				{
					return false;
				}
				else
				{
					return get<2>(pl) < get<2>(pr);
				}
			}
			else
			{
				return get<1>(pl) < get<1>(pr);
			}
		}
		else
		{
			return get<0>(pl) < get<0>(pr);
		}
	};

	sort(_book.begin(), _book.end(), compare);
}

void PhoneBook::SortByPhone()
{
	auto compare = [](BookItem left, BookItem right) -> bool
	{
		PersonPhone pl = left.second->GetFullPhone();
		PersonPhone pr = right.second->GetFullPhone();

		if (get<0>(pl) == get<0>(pr))
		{
			if (get<1>(pl) == get<1>(pr))
			{
				if (get<2>(pl) == get<2>(pr))
				{
					if (get<3>(pl) == get<3>(pr))
					{
						return false;
					}
					else
					{
						return get<3>(pl) < get<3>(pr);
					}
				}
				else
				{
					return get<2>(pl) < get<2>(pr);
				}
			}
			else
			{
				return get<1>(pl) < get<1>(pr);
			}
		}
		else
		{
			return get<0>(pl) < get<0>(pr);
		}
	};

	sort(_book.begin(), _book.end(), compare);

}

PhoneNumberResponse PhoneBook::GetPhoneNumber(wstring surname)
{
	PhoneNumberResponse response;
	wstring message(L"not found");
	PhoneNumber* phoneNumber = nullptr;

	auto compareBySurname = [&surname](BookItem item) -> bool
	{
		wstring sname = get<0>(item.first->GetFullName());
		bool b = sname == surname;
		return get<0>(item.first->GetFullName()) == surname;
	};

	auto current = find_if(_book.begin(), _book.end(), compareBySurname);
	if (current != _book.end())
	{
		message = L"";
		phoneNumber = (*current).second;
	}

	while (current != _book.end())
	{
		current = find_if(++current, _book.end(), compareBySurname);

		if (current != _book.end())
		{
			message = L"found more than 1";
			phoneNumber = nullptr;
			break;
		}
	}

	return make_tuple(message, phoneNumber != nullptr ? optional<const PhoneNumber*>(phoneNumber) : nullopt);

}

void PhoneBook::ChangePhoneNumber(Person p, const PhoneNumber& pn)
{
	auto personEqual = [&p](BookItem item) -> bool
	{
		return *item.first == p;
	};
	auto item = find_if(_book.begin(), _book.end(), personEqual);
	if (item != _book.end())
	{
		auto number = ((*item).second);
		((*item).second) = new PhoneNumber(pn);
		delete number;
	}

	while (item != _book.end())
	{
		item = find_if(++item, _book.end(), personEqual);
		if (item != _book.end())
		{
			auto number = ((*item).second);
			((*item).second) = new PhoneNumber(pn);
			delete number;
		}
	}
}
