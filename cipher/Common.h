#pragma once
#define OUT

#include <string>
using namespace std;

const size_t BUFFER_SIZE = 16'384; // byte count (2 Mb) per thread
const string ENCRYPT_COMMAND = "e";
const string DECRYPT_COMMAND = "d";
const string FILEPATH_COMMAND = "path";
const string KEY_COMMAND = "key";