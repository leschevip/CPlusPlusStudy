#include <iostream>
#include <string>
#include "getopt.h"
#include "cipher.h"
#include <fstream>



using namespace std;
using namespace CipherData;

extern const string ENCRYPT_COMMAND;
extern const string DECRYPT_COMMAND;

int main(size_t n, char** args)
{
	try
	{
		const string path("C:\\Users\\lesch\\Documents\\Visual Studio 2019\\file.txt");
		
		
		const string encLogPath("C:\\Users\\lesch\\Documents\\Visual Studio 2019\\encrypt-log.txt");
		ofstream flog(encLogPath);
		if (flog.is_open())
		{
			Cipher c(flog);
			c.Encrypt(path, 29101987);
		}
	
		
		const string decLogPath = "C:\\Users\\lesch\\Documents\\Visual Studio 2019\\decrypt-log.txt";
		ofstream flog_dec(decLogPath);
		if (flog_dec.is_open())
		{
			Cipher c(flog_dec);
			c.Decrypt(path, 29101987);
		}
		

		
	}
	catch (exception& e)
	{
		cout << e.what();
		throw;
	}
	return 0;
}