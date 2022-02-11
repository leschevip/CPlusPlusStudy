#pragma once

#include <string>
#include <stdexcept>
#include "getopt.h"
#include "CipherAction.h";

using namespace std;

namespace CipherData
{
	struct CipherContext
	{
		CipherAction Action;
		uint32_t Key;
		string FilePath;
	};
}