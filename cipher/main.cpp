#include <iostream>
#include <string>
#include "getopt.h"
#include "FileCipher.h"
#include <fstream>
#include "common.h"



using namespace std;
using namespace CipherData;

int main(size_t n, char** args)
{
	try
	{
		auto cmds = getopt(args, n);
		Option cmdOpt;
		cmdOpt = getopt(cmds, ENCRYPT_COMMAND.c_str());
		if (cmdOpt.Empty())
		{
			cmdOpt = getopt(cmds, DECRYPT_COMMAND.c_str());
		}
		Option key = getopt(cmds, KEY_COMMAND.c_str());
		Option path = getopt(cmds, FILEPATH_COMMAND.c_str());

		if (cmdOpt.Empty() || key.Empty() || path.Empty())
			throw;

		FileCipher c(path.Val);
		if (cmdOpt.Key == ENCRYPT_COMMAND)
			c.Encrypt(stoi(key.Val));
		else
			c.Decrypt(stoi(key.Val));

		/*
		const string path("C:\\Users\\lesch\\Documents\\Visual Studio 2019\\file.txt");
		
		
		const string encLogPath("C:\\Users\\lesch\\Documents\\Visual Studio 2019\\encrypt-log.txt");
		const string decLogPath = "C:\\Users\\lesch\\Documents\\Visual Studio 2019\\decrypt-log.txt";

		int32_t i = 29101987;
		auto ii = i / 100000000;

		FileCipher c(path);
		c.Encrypt(29101987); // тут выполняется savedata и после этого файл все еще 12 байт

		c.Decrypt(29101987); // тут выполняется savedata и после этого файл 15 байт
		*/
	}
	catch (exception& e)
	{
		cout << e.what();
		throw;
	}
	cout << "Seccess!";
	return 0;
}