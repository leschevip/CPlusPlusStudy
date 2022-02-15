#include "CipherBuffer.h"

namespace CipherData
{

	CipherBuffer::CipherBuffer() : _lastPartIndex(0), _parts(0)
	{
	}

	CipherBuffer::~CipherBuffer()
	{
		for (auto* data : _bufferList)
		{
			delete data;
		}
		_bufferList.clear();
	}

	

	size_t CipherBuffer::PartsCount()
	{
		return _parts;
	}
	

	BufferData::BufferData() : Buffer(nullptr), Count(0), Index(0)
	{
	}

	BufferData::~BufferData()
	{
		delete[] Buffer;
	}
}
