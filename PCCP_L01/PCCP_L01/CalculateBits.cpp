#include "CalculateBits.h"

CalculateBits::CalculateBits()
{
}


CalculateBits::~CalculateBits()
{
}

unsigned char cheating[] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3,
4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2,
3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4,
5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2,
3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4,
5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5,
6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3,
4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3,
4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6,
7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4,
5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5,
6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8 };

void CalculateBits::calcBit(fs::path path, uintmax_t *ones, uintmax_t *sumSize) {

		boost::iostreams::mapped_file_source file;
		file.open(path);

		// Check if file was successfully opened
		if (file.is_open()) {
			countBits(file, ones, sumSize);
			file.close();
		}
		else {
			//TODO implement different openmethod for files that can't be open by boost
			fprintf(stderr, "Couldn't open file: %s", path);
		}
}

void CalculateBits::countBits(boost::iostreams::mapped_file_source file, uintmax_t *ones, uintmax_t *sumSize) {
	
	//TODO implement multi Threading

	uintmax_t tempOnes = 0;
	// Get pointer to the data
	const char* data = file.data();
	for (uintmax_t i = 0; i < file.size(); ++i)
	{
		unsigned char temp = static_cast<unsigned char>(data[i]);
		tempOnes += cheating[temp];
	}

	//this->mtx.lock();
	*ones += tempOnes;
	*sumSize += file.size();
	//this->mtx.unlock();
}

void CalculateBits::setMaxThreads(unsigned int maxThreads) {
	this->maxThreads = maxThreads;
}

void CalculateBits::joinThreads() {
	//TODO implement wait for all Threads
}

