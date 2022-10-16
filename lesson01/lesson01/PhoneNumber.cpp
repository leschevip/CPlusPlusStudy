#include "PhoneNumber.h"

wostream& operator << (wostream& out, const PhoneNumber& p)
{
	out << get<0>(p._data) << "(" << get<1>(p._data) << ")" << get<2>(p._data);
	if (get<3>(p._data))
	{
		out << " " << *(get<3>(p._data));
	}
	return out;
}

bool operator == (const PhoneNumber& v1, const PhoneNumber& v2)
{
	return  tie(get<0>(v1._data),
				get<1>(v1._data),
				get<2>(v1._data),
				get<3>(v1._data)) ==
			tie(get<0>(v2._data),
				get<1>(v2._data),
				get<2>(v2._data),
				get<3>(v2._data));
}

bool operator < (const PhoneNumber& v1, const PhoneNumber& v2)
{
	return  tie(get<0>(v1._data),
				get<1>(v1._data),
				get<2>(v1._data),
				get<3>(v1._data)) <
			tie(get<0>(v2._data),
				get<1>(v2._data),
				get<2>(v2._data),
				get<3>(v2._data));
}

PhoneNumber::PhoneNumber()
	: _data(make_tuple(0, 0, L"", nullopt))
{
}

PhoneNumber::PhoneNumber(const PhoneNumber& pn)
{
	_data = make_tuple(get<0>(pn._data), get<1>(pn._data), get<2>(pn._data), get<3>(pn._data));
}

PhoneNumber::PhoneNumber(int countryCode, int cityCode, wstring number, optional<int> addcode)
	: _data(make_tuple(countryCode, cityCode, number, addcode))
{
}

void PhoneNumber::SetCountryCode(int code)
{
	get<0>(_data) = code;
}

void PhoneNumber::SetCityCode(int code)
{
	get<1>(_data) = code;
}

void PhoneNumber::SetNumber(wstring number)
{
	get<2>(_data) = number;
}

void PhoneNumber::SetAddCode(optional<int> code)
{
	get<3>(_data) = code;
}

PersonPhone& PhoneNumber::GetFullPhone()
{
	return _data;
}
