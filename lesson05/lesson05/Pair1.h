#pragma once

template<typename T = int>
class Pair1
{
private:
	T K;
	T V;
public:

	Pair1(T key, T val) : K(key), V(val)
	{

	}

	T first() const { return K; }

	T second() const { return V; }

};
