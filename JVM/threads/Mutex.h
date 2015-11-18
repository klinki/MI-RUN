#pragma once
#include <mutex>
class Mutex
{
protected:
	std::mutex mutex;

public:
	void lock()
	{
		mutex.lock();
	}

	void unlock()
	{
		mutex.unlock();
	}
};
