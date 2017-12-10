#include "CalculateBits.h"

mutex mtx;

CalculateBits::CalculateBits()
{
}


CalculateBits::~CalculateBits()
{
}


void CalculateBits::calcBit(vector<fs::path> path, unsigned long *zeros, unsigned long *ones) {
	
	unsigned long tempZeros;
	unsigned long tempOnes;
	//TODO calc bytes here
	tempOnes = 2;
	tempZeros = 1;

	mtx.lock();
	*zeros += tempZeros;
	*ones += tempOnes;
	mtx.unlock();

}