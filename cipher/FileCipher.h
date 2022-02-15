#pragma once
#include "cipher.h"

namespace CipherData
{
	class FileCipher : public Cipher
	{
	private:
		string _filePath;
		void ExecAction(CipherAction action, long long key);
	public:
		FileCipher(const string& filePath);
		FileCipher(const string& filePath, const string logPath, const bool disableLogging = true);
		void Encrypt(const long long key) override;
		void Decrypt(const long long key) override;
	};
}
