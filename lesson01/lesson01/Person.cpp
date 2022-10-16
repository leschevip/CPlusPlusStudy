#include "Person.h"

wostream& operator << (wostream& out, const Person& p)
{
	out << get<0>(p._data) << " " << get<1>(p._data) << " " << (get<2>(p._data) ? *get<2>(p._data) : L"");
	return out;
}

bool operator == (const Person& v1, const Person& v2)
{
	return tie(get<0>(v1._data), get<1>(v1._data), get<2>(v1._data)) == tie(get<0>(v2._data), get<1>(v2._data), get<2>(v2._data));
}

bool operator < (const Person& v1, const Person& v2)
{
	return tie(get<0>(v1._data), get<1>(v1._data), get<2>(v1._data)) < tie(get<0>(v2._data), get<1>(v2._data), get<2>(v2._data));
}

Person::Person()
	: _data(make_tuple(L"", L"", nullopt))
{
}

Person::Person(wstring surname, wstring name, optional<wstring> patronymic)
	: _data(make_tuple(surname, name, patronymic))

{
}

void Person::SetName(wstring name)
{
	get<1>(_data) = name;
}

void Person::SetSurname(wstring surname)
{
	get<0>(_data) = surname;
}

void Person::SetPatronymic(optional<wstring> patronymic)
{
	get<2>(_data) = patronymic;
}

wstring& Person::GetName()
{
	return get<1>(_data);
}

wstring& Person::GetSurName()
{
	return get<0>(_data);
}

wstring& Person::GetPatronymic()
{
	return (get<2>(_data) ? *get<2>(_data) : _emptyval);
}

PersonName& Person::GetFullName()
{
	return _data;
}
