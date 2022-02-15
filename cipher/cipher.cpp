#include "cipher.h"


namespace CipherData
{
	void Cipher::getMap(const CipherAction action, const size_t key, OUT unordered_map<char, char>* mapReplace, OUT PermutationMap* mapPermutation)
	{
		constexpr int32_t left = numeric_limits<char>::min();
		constexpr int32_t right = numeric_limits<char>::max();
		constexpr int32_t length = right - left;
		const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
		srand(key);

		vector<char> rands;
		const auto coef = fraction * (right - left + 1) + left;
		int32_t nextChar = left;
		int32_t index = 0;

		while (nextChar <= right)
		{
			auto randChar = static_cast<char>(rand() * coef);
			if (find(rands.begin(), rands.end(), randChar) == rands.end())
			{
				rands.push_back(randChar);
				if (action == CipherAction::Encrypt)
				{
					mapReplace->insert({ nextChar, randChar });
				}
				else
				{
					mapReplace->insert({ randChar, nextChar  });
				}
				
				index++;

				nextChar++;
			}
		}

		string str = to_string(key);
		mapPermutation->CountPerBlock = str.size();
		mapPermutation->Origin = new int32_t[mapPermutation->CountPerBlock];
		mapPermutation->Permutation = new int32_t[mapPermutation->CountPerBlock];
		int32_t inc(0);
		size_t t(0);
		for (size_t i = 0; i < 10; i++)
		{
			size_t k = str.find(to_string(i));
			while (k != string::npos)
			{
				if (action == CipherAction::Encrypt)
				{
					mapPermutation->Origin[k] = inc;
					mapPermutation->Permutation[t++] = inc;
				}
				else
				{
					mapPermutation->Permutation[k] = inc;
					mapPermutation->Origin[t++] = inc;
				}
				
				k = str.find(to_string(i), k + 1);
				inc++;
			}
		}

	}

	void Cipher::applyReplace(const BufferData* const data, const unordered_map<char, char>* const map)
	{
		for (size_t k = 0; k < data->Count; k++)
			data->Buffer[k] = map->at(data->Buffer[k]);
	}

	void Cipher::applyPermutation(const BufferData* const data, const PermutationMap* const map)
	{
		size_t parts = ceil(static_cast<double>(data->Count) / map->CountPerBlock);
		size_t shift(0);
		char* tmp = new char[map->CountPerBlock];
		for (size_t p = 0; p < parts - 1; p++)
		{
			for (size_t d = 0; d < map->CountPerBlock; d++)
			{
				tmp[map->Permutation[d]] = data->Buffer[shift + map->Origin[d]];
			}

			for (size_t d = 0; d < map->CountPerBlock; d++)
			{
				data->Buffer[shift + d] = tmp[d];
			}
			shift += map->CountPerBlock;
		}

		delete[] tmp;
	}

	Cipher::Cipher() : _buffer(nullptr), _disableLogging(true)
	{
	}

	Cipher::~Cipher()
	{
		_log.close();
	}

	Cipher::Cipher(const string logPath, const bool disableLogging) : _logPath(logPath), _disableLogging(disableLogging), _buffer(nullptr)
	{
		_log = ofstream(logPath);
	}

	void Cipher::PrintAction(const CipherAction action)
	{
		if (!_disableLogging && _log.is_open())
		{
			_log << "Action: " << (int)action << endl;
		}
	}

	void Cipher::PrintMapReplace(const unordered_map<char, char>* const map)
	{
		if (!_disableLogging && _log.is_open())
		{
			_log << "Map Replace:" << endl;
			_log << "From (For): ";
			auto iter = map->begin();
			while (iter != map->end())
			{
				_log << (int32_t)(*iter).first << "(" << (*iter).first << ") for " << (int32_t)(*iter).second << "(" << (*iter).second << ")";
				_log << endl;
				iter++;
			}
			_log << endl;
		}
	}

	void Cipher::PrintBuffer(const BufferData* const data, const string header)
	{
		if (!_disableLogging && _log.is_open())
		{
			_log.width();
			_log << header << "buffer:" << endl;
			//_log.width(6);
			for (size_t i = 0; i < data->Count; i++)
				_log << (int32_t)data->Buffer[i] << "  ";

			_log.width();
			_log << endl;
		}
	}

	PermutationMap::PermutationMap() : Origin(nullptr), Permutation(nullptr), CountPerBlock(0)
	{
	}

	PermutationMap::~PermutationMap()
	{
		delete[] Origin;
		Origin = nullptr;
		delete[] Permutation;
		Permutation = nullptr;
	}

}