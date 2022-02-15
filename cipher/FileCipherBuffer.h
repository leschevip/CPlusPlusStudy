#pragma once
#include "CipherBuffer.h"

namespace CipherData
{

	class FileCipherBuffer : public CipherBuffer
	{
	private:
		ifstream _file;
		string _filePath;
		size_t _length;
	public:
		FileCipherBuffer(string file);
		~FileCipherBuffer();
		void Reset() override;
		BufferData* Data(size_t index) override;
		void SaveData() override;
	};

}