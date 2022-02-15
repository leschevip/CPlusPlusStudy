#pragma once
#include <string>
#include <stdexcept>
#include <fstream>
#include <vector>
#include "Common.h"

using namespace std;

namespace CipherData
{


	class BufferData
	{
	public:
		size_t Index;
		char* Buffer;
		size_t Count;
		BufferData();
		~BufferData();
	};
	


	class CipherBuffer
	{
	protected:
		size_t _parts;
		size_t _lastPartIndex;
		vector<BufferData*> _bufferList;
	public:
		CipherBuffer();
		~CipherBuffer();
		size_t PartsCount();
		virtual void Reset() = 0;
		virtual BufferData* Data(size_t index) = 0;
		virtual void SaveData() = 0;
	};

}
