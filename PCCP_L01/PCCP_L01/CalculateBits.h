#pragma once

#include "stdafx.h"
#include <string>
#include <thread>
#include<mutex>
#include <boost\filesystem\path.hpp>

using namespace std;
namespace fs = boost::filesystem;

class CalculateBits
{
public:
	CalculateBits();
	~CalculateBits();
	void calcBit(vector<fs::path> path, unsigned long *zeros, unsigned long *ones);
};

