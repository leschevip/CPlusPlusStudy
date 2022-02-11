#include "cipher.h"
#include <io.h>


namespace CipherData
{
	const size_t BUFFER_SIZE = 16'384; // byte count (2 Mb) per thread
	//const size_t BUFFER_SIZE = 200; // byte count (2 Mb) per thread

	CharMap* Cipher::getMaps(const int key)
	{
		CharMap* map = new CharMap();
		constexpr int32_t left = numeric_limits<char>::min();
		constexpr int32_t right = numeric_limits<char>::max();
		const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
		srand(key);

		for (int32_t i = 0; i < right - left; i++)
		{
			map->Origin[i] = i + left;

			const auto coef = fraction * (right - left + 1) + left;
			map->Replace[i] = static_cast<char>(rand() * coef);
		}

		constexpr int32_t uleft = numeric_limits<unsigned char>::min();
		constexpr int32_t uright = numeric_limits<unsigned char>::max();
		for (int32_t i = 0; i < right - uleft; i++)
		{
			const auto coef = fraction * (uright - uleft + 1) + uleft;
			map->Permutation[i] = static_cast<char>(rand() * coef);
		}
		
		return map;
	}

	void Cipher::encryptReplace(char* buff, size_t size, CharMap* map)
	{
		for (size_t i = 0; i < size; i++)
		{
			for (size_t k = 0; k < 255; k++)
				if (buff[i] == map->Origin[k])
					buff[i] ^= map->Replace[k];
		}
			
	}

	void Cipher::decryptReplace(char* buff, size_t size, CharMap* map)
	{
		for (size_t i = 0; i < size; i++)
		{
			for (size_t k = 0; k < 255; k++)
				if (buff[i] == map->Replace[k])
					buff[i] ^= map->Origin[k];
		}
			
	}

	void Cipher::encryptPermutation(char* buff, size_t size, char* permutation)
	{
		const constexpr int32_t charMin = numeric_limits<char>::min();
		const int32_t left = abs(charMin);
		for (size_t i = 0; i < size; i++)
			buff[i] = permutation[i];
	}

	
	//Cipher::Cipher() { }

	Cipher::Cipher(ofstream& flog) : _flog(flog)
	{
	}

	void Cipher::Encrypt(const string filePath, const int key)
	{
		CharMap* map = getMaps(key);

		ifstream f(filePath);
		f.seekg(0, ios::end);
		size_t length = f.tellg();
		f.seekg(0, ios::beg);
		auto parts = ceil(static_cast<double>(length) / BUFFER_SIZE);
		char** res = new char* [parts];
		size_t curPos = 1;
		for (size_t i = 0; i < parts; i++)
		{
			const auto count = (length - curPos > BUFFER_SIZE ? BUFFER_SIZE : length - curPos);
			char* buffer = new char[count];
			f.read(buffer, count);
			
			encryptReplace(buffer, count, map);
			res[i] = buffer;
			curPos += count;
		}

		f.close();
		
		//ofstream fout("C:\\Users\\lesch\\Documents\\Visual Studio 2019\\out");
		ofstream fout(filePath);
		curPos = 1;
		for (size_t i = 0; i < parts; i++)
		{
			const auto count = (length - curPos > BUFFER_SIZE ? BUFFER_SIZE : length - curPos);
			//fout.seekp(curPos);
			fout.write(res[i], count);
			curPos += count;
		}
		fout.close();

		ifstream f1(filePath);
		f1.seekg(0, ios::end);
		length = f1.tellg();
		f1.seekg(0, ios::beg);
		f1.close();
	}

	void Cipher::Decrypt(const string filePath, const int key)
	{
		CharMap* map = getMaps(key);

		ifstream f(filePath);
		f.seekg(0, ios::end);
		size_t length = f.tellg();
		f.seekg(0, ios::beg);
		auto parts = ceil(static_cast<double>(length) / BUFFER_SIZE);
		char** res = new char* [parts];
		size_t curPos = 1;
		for (size_t i = 0; i < parts; i++)
		{
			const auto count = (length - curPos > BUFFER_SIZE ? BUFFER_SIZE : length - curPos);
			char* buffer = new char[count];
			f.read(buffer, count);

			decryptReplace(buffer, count, map);
			res[i] = buffer;
			curPos += count;
		}

		f.close();

		ofstream fout(filePath);
		curPos = 1;
		for (size_t i = 0; i < parts; i++)
		{
			const auto count = (length - curPos > BUFFER_SIZE ? BUFFER_SIZE : length - curPos);
			//fout << res[i];
			//fout.seekp(curPos);
			fout.write(res[i], count);
			curPos += count;
		}

		fout.close();
	}

	void Cipher::Execute(CipherContext context)
	{
		if (context.Action == CipherAction::Encrypt)
			Encrypt(context.FilePath, context.Key);
		if (context.Action == CipherAction::Decrypt)
			Decrypt(context.FilePath, context.Key);
	}

}