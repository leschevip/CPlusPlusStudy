#include "getopt.h";

using namespace std;

const char COMMAND_MARKER = '-';

Option getopt(char** args, const size_t size, const char* argk)
{
	vector<Option> pairs = getopt(args, size);
	return getopt(pairs, argk);
}

Option getopt(vector<Option>& options, const char* argk)
{
	string key(argk);
	auto predicate = [&key](Option o) {
		return o.Key == key;
	};
	auto res = std::find_if(options.begin(), options.end(), predicate);
	if (res != options.end())
	{
		return *res;
	}
	else
	{
		return Option();
	}
}

vector<Option> getopt(char** args, const size_t size)
{	
	size_t i(1);
	// check first par. It can't be value
	if (args[i][0] != COMMAND_MARKER)
	{
		throw invalid_argument("First argument must be a parameter");
	}

	vector<Option> pairs;
	
	do
	{
		if (args[i][0] == COMMAND_MARKER)
		{
			string key(args[i]);
			string val("");
			if (i < size - 1 && args[i + 1][0] != COMMAND_MARKER)
			{
				i++;
				val.assign(args[i]);
			}

			pairs.push_back({ key.substr(1), val });
		}
		else
		{
			throw invalid_argument("Invalid parameter " + string(args[i]));
		}
		i++;
	} 
	while (i < size-1);

	return pairs;
}

bool Option::Empty()
{
	return (Key == "");
}
