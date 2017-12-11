#pragma once

#include "stdafx.h"
#include <string>
#include <regex>
#include <boost\filesystem\path.hpp>
#include <boost\filesystem\operations.hpp>
#include <boost\algorithm\string.hpp>
#include "CalculateBits.h"

using namespace std;
namespace fs = boost::filesystem;

class Directories
{
public:
	Directories(unsigned int maxThreads, uintmax_t* resultOnes, uintmax_t* resultSize);
	~Directories();
	void generateFileTree(vector<string> pathes, vector<string> filter, int maxDepth);

private:
	unsigned int maxThreads;
	uintmax_t* resultOnes;
	uintmax_t* resultSize;
	CalculateBits calculateBits;
	void getFiles(fs::path path, int maxDepth);
	void getFiles(fs::path path, vector<regex> filters, int maxDepth);
	void splitFilters(vector<string> filters, vector<regex> *returnValue);
};

