#pragma once
#include <string>
#include <stdexcept>
#include <fstream>
#include <vector>

using namespace std;

namespace CipherData
{
	

	class CipherProcessor
	{
	private:
		size_t _parts;
		char* _buffer;
		size_t _lastPartIndex;
		vector<char*> _bufferList;
	public:
		CipherProcessor(ifstream& file);
		size_t PartsCount();
		char* Data(size_t index, bool reUseLast = true);
	};
}
