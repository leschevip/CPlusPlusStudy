#include "Date.h"
#include "Game.h"

using namespace std;


void Task1()
{
	unique_ptr<Date> today = make_unique<Date>(2022, 9, 5);
	cout << today->GetYear() << endl << today->GetMonth() << endl << today->GetDay() << endl;
	cout << *today.get() << endl;
	
	cout << today.get() << endl;
	unique_ptr<Date> date = move(today);
	cout << today.get() << endl;
	cout << date.get() << endl;
}

void Task2()
{
	shared_ptr<Date> d1 = make_shared<Date>(2022, 9, 5);
	shared_ptr<Date> d2 = make_shared<Date>(2022, 10, 29);
	shared_ptr<Date> max = maxDate(d1, d2);
	cout << d1.get() << " " << d1.use_count() << endl;
	cout << d2.get() << " " << d2.use_count() << endl;
	cout << max.get() << " " << max.use_count() << endl;

	cout << endl;

	cout << *d1.get() << endl;
	cout << *d2.get() << endl;
	swapDates(d1, d2);
	cout << d1.get() << " " << d1.use_count() << endl;
	cout << d2.get() << " " << d2.use_count() << endl;
	cout << max.get() << " " << max.use_count() << endl;
	cout << *d1.get() << endl;
	cout << *d2.get() << endl;
}

void BlackJackMain()
{
	bool repeat = true;
	while (repeat)
	{
		system("cls");
		vector<string> names;
		size_t count = Input<size_t>("players count");
		for (size_t i = 1; i <= count; i++)
			names.push_back(Input<string>("player name"));

		Game gm(names);
		gm.Play();

		repeat = Input<bool>("repeat game? (0 - No / 1 - Yes)");
	}
}

void main()
{
	Task1();

	Task2();

	BlackJackMain();
}