#include "FileCipher.h"

namespace CipherData
{
	void FileCipher::ExecAction(CipherAction action, long long key)
	{
		PrintAction(action);

		unordered_map<char, char> mapReplace; 
		PermutationMap mapPermutation;

		this->getMap(action, key, &mapReplace, &mapPermutation);
		PrintMapReplace(&mapReplace);
		for (size_t i = 0; i<_buffer->PartsCount(); i++)
		{
			auto* data = _buffer->Data(i);
			PrintBuffer(data, "Before replace ");
			applyReplace(data, &mapReplace);

			applyPermutation(data, &mapPermutation);
			PrintBuffer(data, "After permutation ");
		}
	}

	FileCipher::FileCipher(const string& filePath) : FileCipher(filePath, "", true)
	{
	}

	FileCipher::FileCipher(const string& filePath, const string logPath, const bool disableLogging) : Cipher(logPath, disableLogging)
	{
		_buffer = (CipherBuffer*)(new FileCipherBuffer(filePath));
	}
	
	void FileCipher::Encrypt(const long long key)
	{
		_buffer->Reset();
		ExecAction(CipherAction::Encrypt, key);
		_buffer->SaveData();
	}

	void FileCipher::Decrypt(const long long key)
	{
		_buffer->Reset();
		ExecAction(CipherAction::Decrypt, key);
		_buffer->SaveData();
	}
}

