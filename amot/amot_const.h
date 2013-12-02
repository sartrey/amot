#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>

#include "windows.h" //#IFDEF

#ifdef AMOT_EXPORTS
#define AMOT_API __declspec(dllexport)
#else
#define AMOT_API __declspec(dllimport)
#endif

namespace amot
{
	//using namespace
	using std::vector;
	using std::string;
	using std::wstring;
	using std::invalid_argument;

	//define type
	typedef void* object;
	typedef unsigned char byte;
	typedef char int8;
	typedef short int16;
	typedef int int32;
	typedef long long int64;
	typedef unsigned char uint8;
	typedef unsigned short uint16;
	typedef unsigned int uint32;
	typedef unsigned long long uint64;
	typedef float real32;
	typedef double real64;
	typedef const char* cstr;
	typedef const wchar_t* cwstr;

	#define null 0
}