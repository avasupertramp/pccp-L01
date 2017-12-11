#pragma once

#include "stdafx.h"

#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include<mutex>
#include <boost\iostreams\device\mapped_file.hpp>
#include <boost\filesystem.hpp>
#include <boost\filesystem\path.hpp>

using namespace std;
namespace fs = boost::filesystem;

class CalculateBits
{
public:
	CalculateBits();
	~CalculateBits();
	void calcBit(fs::path path, uintmax_t *ones, uintmax_t *sumSize);
	void setMaxThreads(unsigned int maxThreads);
	void joinThreads();
private:
	mutex mtx;
	unsigned int maxThreads;
	void countBits(boost::iostreams::mapped_file_source file, uintmax_t *ones, uintmax_t *sumSize);
};

