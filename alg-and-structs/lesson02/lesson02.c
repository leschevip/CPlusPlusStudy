#include <stdio.h>

/*

@startuml
start
:input VALUE;
:isPrime = 0;
if (VALUE >= 2) then (Yes)
	if (VALUE is even number) then (Yes)
		if (VALUE = 2) then (Yes)
			:isPrime = 1;
		else
			:isPrime = 0;
		endif;
	else
		:isPrime = 1;
		:k = 2;
		while (k < VALUE) is (Yes)
			if (VALUE % k == 0) then (Yes)
				:isPrime = 0;
				break;
			else (No)
				:k++;
			endif;
		endwhile (No)
	endif
endif

:return IsPrime;
end
@enduml

@startuml
start
:FROM = 1;
:TO = 10;
:SUM = 0;
while (FROM <= TO) is (Yes)
	:SUM += FROM;
	:FROM++;
endwhile (No)
:return SUM;
end
@enduml

*/


int IsSimplValue(int value)
{
	int isPrime = 0;
	if (value >= 2)
	{
		if ((value & 1) == 0)
		{
			if (value == 2)
			{
				isPrime = 1;
			}
			else
			{
				isPrime = 0;
			}
		}
		else
		{
			isPrime = 1;
			for(int n = 2; n < value; n++)
			{
				if (!(value % n))
				{
					isPrime = 0;
					break;
				}
			}
		}
	}

	return isPrime;
}

int main(int argv, char** argc)
{
	int v;
	printf("%s", "Input value:\n");
	scanf("%d", &v);
	printf("Is value simple: %d\n", IsSimplValue(v));
}


