
#include "Helper.h"

string genderToString(Gender gender)
{
	switch (gender)
	{
	case Gender::Male:
		return "Male";
	case Gender::Female:
		return "Female";
	case Gender::Others:
		return "Others";
	default:
		return "Uknown";
	}
}