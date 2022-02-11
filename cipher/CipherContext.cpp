#include "CipherContext.h"

const string ENCRYPT_COMMAND = "e";
const string DECRYPT_COMMAND = "d";
const string KEY_VALUE_COMMAND = "key";
const string FILE_PATH_COMMAND = "f";

namespace CipherData
{

	CipherAction getAction(const string& option)
	{
		if (option == ENCRYPT_COMMAND)
		{
			return CipherAction::Encrypt;
		}
		else if (option == DECRYPT_COMMAND)
		{
			return CipherAction::Decrypt;
		}
		else
		{
			throw invalid_argument("Uknown command " + option);
		}
	}

	CipherContext parseCommandLine(size_t argsCount, char** args)
	{
		CipherContext context;
		auto options = getopt(args, argsCount);
		for (auto option : options)
		{
			if (option.Key == ENCRYPT_COMMAND || option.Key == DECRYPT_COMMAND)
			{
				context.Action = getAction(option.Key);
			}
			if (option.Key == KEY_VALUE_COMMAND)
			{
				context.Key = stoi(option.Val);
			}
			if (option.Key == FILE_PATH_COMMAND)
			{
				context.FilePath = option.Val;
			}
		}
		if (context.Action == CipherAction::Empty)
			throw exception("Encrypt / Decrypt action command not found");

		if (context.Key == 0)
			throw exception("Encrypt / Decrypt key not found");

		if (context.FilePath == "")
			throw exception("FilePath not found");

		return context;
	}
}