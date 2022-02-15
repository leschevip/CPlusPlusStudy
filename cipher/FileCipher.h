#pragma once
#include "cipher.h"

namespace CipherData
{
	class FileCipher : public Cipher
	{
	private:
		string _filePath;
		void ExecAction(CipherAction action, size_t key);
	public:
		FileCipher(const string filePath);
		FileCipher(const string filePath, const string logPath, const bool disableLogging = true);
		void Encrypt(const size_t key) override;
		void Decrypt(const size_t key) override;
	};
}
