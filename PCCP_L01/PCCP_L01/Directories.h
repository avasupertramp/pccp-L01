#pragma once

#include "stdafx.h"
#include <string>
#include <boost\filesystem\path.hpp>
#include <boost\filesystem\operations.hpp>
#include <boost\algorithm\string.hpp>

using namespace std;
namespace fs = boost::filesystem;

class Directories
{
public:
	Directories();
	~Directories();
	void generateFileTree(vector<string> pathes, vector<string> filter, int maxDepth);

private:
	void getFiles(fs::path path, vector<fs::path> *files, vector<string> filters, int maxDepth);
	void splitFilters(vector<string> filters, vector<string> *returnValue);
};

