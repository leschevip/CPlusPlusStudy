#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <list>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>


using namespace std;

template<typename V, typename IBeg, typename IEnd>
void unique_print(IBeg beg, IEnd end)
{
	set<V> uq;
	while (beg != end)
	{
		auto v = *beg;
		if (!uq.contains(v))
		{
			cout << v << endl;
			uq.insert(v);
		}
		beg++;
	}
}

void Task1()
{
	cout << "vector iterator:" << endl;
	vector<string> v;
	v.push_back("You");
	v.push_back("don't");
	v.push_back("have");
	v.push_back("to");
	v.push_back("pay");
	v.push_back("this");
	v.push_back("museum");
	v.push_back("is");
	v.push_back("free");

	v.push_back("You");
	v.push_back("don't");
	v.push_back("have");
	v.push_back("to");
	v.push_back("go");
	v.push_back("to");
	v.push_back("the");
	v.push_back("party");
	v.push_back("if");
	v.push_back("you");
	v.push_back("don't");
	v.push_back("want");
	v.push_back("to");
	v.push_back("to");
	unique_print<string>(begin(v), end(v));

	cout << endl << "list iterator:" << endl;
	list<string> ls;
	ls.push_back("You");
	ls.push_back("don't");
	ls.push_back("have");
	ls.push_back("to");
	ls.push_back("pay");
	ls.push_back("this");
	ls.push_back("museum");
	ls.push_back("is");
	ls.push_back("free");

	ls.push_back("You");
	ls.push_back("don't");
	ls.push_back("have");
	ls.push_back("to");
	ls.push_back("go");
	ls.push_back("to");
	ls.push_back("the");
	ls.push_back("party");
	ls.push_back("if");
	ls.push_back("you");
	ls.push_back("don't");
	ls.push_back("want");
	ls.push_back("to");
	ls.push_back("to");
	unique_print<string>(begin(ls), end(ls));
}

size_t findIndexOfNextSentence(string& str, size_t index, string& delimeter)
{
	size_t iend = str.find(delimeter, index);
	if (iend == numeric_limits<size_t>::max())
		return str.size();

	if (iend == str.size() - 1)
		return iend;

	iend++;
	while (!isspace(str[iend]))
	{
		iend = findIndexOfNextSentence(str, iend, delimeter);
		if (iend == str.size())
			break;
	}

	return iend;
}

void SplitSentences(string& str, string& delimeter, unordered_map<string, int>& m)
{
	int i = 0;
	while (i < str.size())
	{
		pair<string, int> vlu;
		size_t iend = findIndexOfNextSentence(str, i, delimeter);
		size_t shift = iend - i;
		vlu.first = str.substr(i, shift);
		vlu.second = count_if(begin(vlu.first), end(vlu.first), [](char c) {return isspace(c); }) + 1;
		m.insert(vlu);
		i += (shift + 1);
	}
}

void Task2()
{
	string str;
	cout << "Input text:" << endl;
	getline(cin, str);
	int i = 0;
	string delimeter = ".";

	unordered_map<string, int> map;
	SplitSentences(str, delimeter, map);
	vector<pair<string, int>> sentences(begin(map), end(map));
	sort(begin(sentences), end(sentences), [](const auto& l, const auto& r) { return l.second < r.second; });

	cout << endl;
	cout << "Results: " << endl;
	for (auto p : sentences)
	{
		cout << p.first << " : " << p.second << endl;
	}

}

void main()
{
	
	Task1();
	cout << endl;
	Task2();
	cout << endl;
	
}