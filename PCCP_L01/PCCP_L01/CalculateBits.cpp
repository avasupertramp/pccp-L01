#include "CalculateBits.h"

void Worker::operator()()
{
	std::function<void()> task;
	while (true)
	{
		{   // acquire lock
			std::unique_lock<std::mutex>
				lock(pool.queue_mutex);

			// look for a work item
			while (!pool.stop && pool.tasks.empty())
			{ // if there are none wait for notification
				pool.condition.wait(lock);
			}

			if (pool.stop) // exit if the pool is stopped
				return;

			// get the task from the queue
			task = pool.tasks.front();
			pool.tasks.pop_front();

		}   // release lock

			// execute the task
		task();
	}
}

// the constructor just launches some amount of workers
ThreadPool::ThreadPool() : stop(false)
{
}

void ThreadPool::initialize(size_t threads) {
	for (size_t i = 0; i < threads; ++i) {
		workers.push_back(std::thread(Worker(*this)));
	}
}

void ThreadPool::stopWorker() {
	stop = true;
	condition.notify_all();

	// join them
	for (size_t i = 0; i<workers.size(); ++i)
		workers[i].join();
}

// the destructor joins all threads
ThreadPool::~ThreadPool()
{
}

// add new work item to the pool
template<class F>
void ThreadPool::enqueue(F f)
{
	{ // acquire lock
		std::unique_lock<std::mutex> lock(queue_mutex);

		// add the task
		tasks.push_back(std::function<void()>(f));
	} // release lock

	  // wake up one thread
	condition.notify_one();
}

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

void CalculateBits::calcBit(boost::iostreams::mapped_file_source* file, uintmax_t *ones, uintmax_t *sumSize) {

	try
	{		
		// Check if file was successfully opened
//		pool.enqueue([&] {
			if ((*file).is_open()) {
				//countBits(file, ones, sumSize);
			
				size_t length = (*file).size();
	//			pool.enqueue([&] {
					std::uintmax_t tempOnes = 0;
					const char* data = (*file).data();
					for (size_t i = 0; i < length; ++i)
					{
						unsigned char temp = static_cast<unsigned char>(data[i]);
						tempOnes += cheating[temp];
					}
					*ones += tempOnes;
					*sumSize += (*file).size();
					(*file).close();
	//			});
			}
//		});
		//else {
		//	//TODO could be improved
		//	ifstream in(path.string());
		//	string contents((std::istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
		//	countBits(contents.c_str(), ones, sumSize);
		//	fprintf(stderr, "Couldn't open file: %s", path);
		//}
	}
	catch (const std::exception&)
	{
		//fprintf(stderr, "Error opening File %s \n", path.string().c_str());
	}

}

void CalculateBits::countBits(boost::iostreams::mapped_file_source *file, uintmax_t *ones, uintmax_t *sumSize) {
	
	//TODO implement multi Threading

	uintmax_t tempOnes = 0;
	// Get pointer to the data
	const char* data = (*file).data();
	try {
		for (uintmax_t i = 0; i < (*file).size(); ++i)
		{
			unsigned char temp = static_cast<unsigned char>(data[i]);
			tempOnes += cheating[temp];
		}
	}
	catch (exception e) {

	}


	//this->mtx.lock();
	*ones += tempOnes;
	*sumSize += (*file).size();
	//this->mtx.unlock();
}

void CalculateBits::countBits(const char* file, size_t length,uintmax_t *ones, uintmax_t *sumSize) {
	//TODO implement multi Threading
	
		std::uintmax_t tempOnes = 0;
		// Get pointer to the data
		//size_t te = strlen(file);
		for (size_t i = 0; i < length; ++i)
		{
			unsigned char temp = static_cast<unsigned char>(file[i]);
			tempOnes += cheating[temp];
		}

		//mtx.lock();
		*ones += tempOnes;
		*sumSize += length;
		//mtx.unlock();

}

void CalculateBits::setMaxThreads(unsigned int maxThreads) {
	this->maxThreads = maxThreads;
	this->pool.initialize(maxThreads);
}

void CalculateBits::joinThreads() {
	this->pool.stopWorker();
}