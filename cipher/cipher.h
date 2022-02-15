#pragma once
#include <string>
#include <functional>
#include <stdexcept>
#include <fstream>
#include <unordered_map>
#include <map>
#include <chrono>
#include <random>
#include "CipherAction.h"
#include "CipherBuffer.h"
#include "FileCipherBuffer.h"


using namespace std;

namespace CipherData
{	
	class PermutationMap
	{
	public:
		int32_t CountPerBlock;
		int32_t* Origin;
		int32_t* Permutation;

		PermutationMap();
		~PermutationMap();
	};

	class Cipher
	{
	protected:
		string _logPath;
		ofstream _log;
		CipherBuffer* _buffer;
		bool _disableLogging;
		void getMap(const CipherAction action, const long long key, OUT unordered_map<char, char>* mapReplace, OUT PermutationMap* mapPermutation);
		void applyReplace(const BufferData* const data, const unordered_map<char, char>* const map);
		void applyPermutation(const BufferData* const data, const PermutationMap* const map);
	public:
		Cipher();
		~Cipher();
		Cipher(const string& logPath, const bool disableLogging);
		void PrintAction(const CipherAction action);
		void PrintMapReplace(const unordered_map<char, char>* const map);
		void PrintBuffer(const BufferData* const data, const string header);
		virtual void Encrypt(const long long key) = 0;
		virtual void Decrypt(const long long key) = 0;
	};
}
