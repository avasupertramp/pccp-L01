#pragma once

#include "stdafx.h"
//#include "ThreadPool.h"

#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <boost\iostreams\device\mapped_file.hpp>
#include <boost\filesystem.hpp>
#include <boost\filesystem\path.hpp>

#include <vector>
#include <deque>
#include <condition_variable>

using namespace std;
namespace fs = boost::filesystem;

// the actual thread pool
class ThreadPool {
public:
	ThreadPool();
	void initialize(size_t threads);
	void stopWorker();
	template<class F>
	void enqueue(F f);
	~ThreadPool();
private:
	friend class Worker;
	// need to keep track of threads so we can join them
	std::vector< std::thread > workers;
	// the task queue
	std::deque<std::function<void()> > tasks;

	// synchronization
	std::mutex queue_mutex;
	std::condition_variable condition;
	bool stop;
};

class Worker {
public:
	Worker(ThreadPool &s) : pool(s) { }
	void operator()();
private:
	ThreadPool & pool;
};

class CalculateBits
{
public:
	CalculateBits();
	~CalculateBits();
	void calcBit(boost::iostreams::mapped_file_source* path, uintmax_t *ones, uintmax_t *sumSize);
	void setMaxThreads(unsigned int maxThreads);
	void joinThreads();
private:
	mutex mtx;
	unsigned int maxThreads;
	ThreadPool pool;
	void countBits(const char* file, size_t length, uintmax_t *ones, uintmax_t *sumSize);
	void countBits(boost::iostreams::mapped_file_source* file, uintmax_t *ones, uintmax_t *sumSize);
};


