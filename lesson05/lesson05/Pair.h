#pragma once

template<typename TKey = int, typename TValue = int>
class Pair
{

protected:
	TKey K;
	TValue V;

public:

	Pair(TKey key, TValue val) : K(key), V(val) { }

	TKey first() const { return K; }

	TValue second() const { return V; }

};
