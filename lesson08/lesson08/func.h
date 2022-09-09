#pragma once

template<typename T1, typename T2>
auto divv(T1 a, T2 b)
{
	if (b == 0)
		throw "DivisionByZero";
	return a / b;
}