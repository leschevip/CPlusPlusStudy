#pragma once
#include <vector>
#include <functional>
#include <string>
#include <stdexcept>

using namespace std;

class Option
{
public:
	string Key;
	string Val;
	bool Empty();
};


Option getopt(char** args, const size_t size, const char* argk);


Option getopt(vector<Option>& options, const char* argk);


vector<Option> getopt(char** args, const size_t size);
