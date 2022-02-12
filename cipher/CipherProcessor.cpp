#include "CipherProcessor.h"

namespace CipherData
{
	const size_t BUFFER_SIZE = 16'384; // byte count (2 Mb) per thread
	//const size_t BUFFER_SIZE = 200; 

	CipherProcessor::CipherProcessor(ifstream& file) : _lastPartIndex(0)
	{
		file.seekg(0, ios::end);
		size_t length = file.tellg();
		file.seekg(0, ios::beg);
		_parts = ceil(static_cast<double>(length) / BUFFER_SIZE);
		_buffer = new char[BUFFER_SIZE];
	}

	size_t CipherProcessor::PartsCount()
	{
		return _parts;
	}
	char* CipherProcessor::Data(size_t index, bool reUseLast = true)
	{
		char* buffer(nullptr);
		if (reUseLast)
		{
			buffer = _buffer;
		}
		else
		{
			buffer = new char[BUFFER_SIZE];
			_bufferList.push_back(buffer);
		}

		file


		return _buffer;
	}
}
