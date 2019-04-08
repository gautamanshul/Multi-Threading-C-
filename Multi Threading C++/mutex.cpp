#include <iostream>
#include <thread>
#include <mutex>

class Counter {
	long val;
	mutable std::mutex mtx;
public:
	Counter(long initial = 0L) : val(initial) {}
	void increment()
	{
		std::lock_guard<std::mutex> guard(mtx);
		++val;
	}

	long value() const {
		std::lock_guard<std::mutex> guard(mtx);

		return val;
	}
};

void use_counter(Counter &c)
{
	for (size_t i = 0; i < 100; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		c.increment();

		std::cout << c.value() << "\n";
	}
}

int main2() 
{
	std::cout << "Counter with Mutex" << std::endl;

	Counter c;

	std::thread t1(use_counter, std::ref(c));
	std::thread t2(use_counter, std::ref(c));

	t1.join();
	t2.join();

	return 0;
}