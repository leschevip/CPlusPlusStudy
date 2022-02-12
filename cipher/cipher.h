#pragma once
#include <string>
#include <stdexcept>
#include <fstream>
#include <unordered_map>
#include "CipherContext.h"


using namespace std;

namespace CipherData
{	
	struct CharMap
	{
		char Origin[255];
		char Replace[255];
		unsigned char Permutation[255];
	};

	class Cipher
	{
	private:
		ofstream& _flog;
		unordered_map<char, char>* getMapReplace(const CipherAction action, const size_t key);
		void applyReplace(ifstream& file, unordered_map<char, char>* map);

		CharMap* getMaps(const int key);
		void encryptReplace(char* buff, size_t size, CharMap* map);
		void decryptReplace(char* buff, size_t size, CharMap* map);
		void encryptPermutation(char* buff, size_t size, char* permutation);
	public:
		//Cipher();
		Cipher(ofstream& flog);
		void Encrypt(const string filePath, const size_t key);
		void Decrypt(const string filePath, const size_t key);
		void Execute(const CipherContext context);
	};
}
