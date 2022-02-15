#include "FileCipherBuffer.h"
#include <algorithm>

namespace CipherData
{

	FileCipherBuffer::FileCipherBuffer(string filePath) : CipherBuffer()
	{
		_filePath = filePath;
		Reset();
	}

	FileCipherBuffer::~FileCipherBuffer()
	{
		if (_file.is_open())
		{
			_file.close();
		}
	}

	void FileCipherBuffer::Reset()
	{
		if (_file.is_open())
			return;
		_file = ifstream(_filePath,  ios::binary);
		_file.seekg(0, ios::end);
		_length = _file.tellg();
		_file.seekg(0, ios::beg);
		_parts = ceil(static_cast<double_t>(_length) / BUFFER_SIZE);
	}

	BufferData* FileCipherBuffer::Data(size_t index)
	{
		size_t pos(0);
		size_t count(0);
		if (index > _parts - 1)
		{
			throw out_of_range("Invalid index");
		}
		else if (index < _parts - 1)
		{
			count = BUFFER_SIZE;
		}
		else
		{
			if (_length > BUFFER_SIZE)
			{
				count = _length - index * BUFFER_SIZE;
			}
			else
			{
				count = _length;
			}
		}
		pos = index * BUFFER_SIZE;

		if (pos >= 0 && pos <= _length - 1)
		{
			_file.seekg(pos, ios_base::beg);
		}
		else
		{
			throw out_of_range("Invalid position of byte in file");
		}

		BufferData* data = new BufferData();
		data->Buffer = new char[count];
		data->Count = count;
		_file.read(data->Buffer, count);

		_bufferList.push_back(data);

		return data;
	}

	void FileCipherBuffer::SaveData()
	{
		sort(_bufferList.begin(), _bufferList.end(), [](BufferData* first, BufferData* second)
		{
			return first->Index < second->Index;
		});

		if (_file.is_open())
		{
			_file.close();
		}

		ofstream outf(_filePath, ios_base::binary);
		
		for (auto* data : _bufferList)
		{ 
			outf.write(data->Buffer, data->Count);
			delete data;
		}
		_bufferList.clear();

		outf.close();
	}

}