#include <iostream>
#include <iomanip>
#include <string>
#include "Input.h"
#include "Player.h"

using namespace std;

void Task1()
{
	int a;
	a = Input<int>(NAME_OF(a));
	cout << a << endl;

	string s;
	s = Input<string>(NAME_OF(s));
	cout << s << endl;
}

ostream& __CLRCALL_OR_CDECL endll (ostream& out) 
{
	out.put(out.widen('\n'));
	out.put(out.widen('\n'));
	out.flush();
	return out;
}

void Task2()
{
	cout << 1 << endll;
	cout << 2 << endll;
}

void Task3()
{
	Card c1(CardSuit::hearts, CardType::King, 4);
	Card c2(CardSuit::clubs, CardType::King, 4);
	Card c3(CardSuit::diamonds, CardType::King, 4);
	Card c4(CardSuit::spades, CardType::King, 4);
	
	Card n1(CardSuit::hearts, CardType::Number, 10);

	wcout << c1 << endl << c2 << endl << c3 << endl << c4 << endl << n1 << endl << endl;

	wstring name = L"Biden";
	GenericPlayer pl(name);
	pl.Add(&c1);
	pl.Add(&c2);
	pl.Add(&c3);
	pl.Add(&c4);
	pl.Add(&n1);

	wcout << pl << endl << endl;

	cout << "That's ok!";
}

void main()
{
	Task1();
	Task2();
	Task3();
}