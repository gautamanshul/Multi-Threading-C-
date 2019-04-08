#include <iostream>
#include <atomic>
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

class Counter2
{
	mutable std::atomic_long val;
public:
	Counter2() : val{} {}
	Counter2(long initial) : val(initial) {}
	void increment() { val++; }
	long value() const { return val.load(); }
};

void use_counter3(Counter &c)
{
	for (size_t i = 0; i < 1000000; i++) {
		c.increment();
	}
}

void use_counter4(Counter2 &c)
{
	for (size_t i = 0; i < 1000000; i++) {
		c.increment();
	}
}

int main4()
{
	
	std::cout << "Counter using atomics" << std::endl;
	using namespace std::chrono;

	//using mutex
	Counter c;
	high_resolution_clock::time_point time1 = high_resolution_clock::now();

	std::thread t1(use_counter3, std::ref(c));
	std::thread t2(use_counter3, std::ref(c));

	t1.join();
	t2.join();
	high_resolution_clock::time_point time2 = high_resolution_clock::now();

	auto duration = duration_cast<microseconds> (time2 - time1).count();
	std::cout << "Duration (mutex): " << duration << "\n";
	std::cout << "Value (mutex): " << c.value() << "\n";

	//using atomic
	Counter2 c2;
	time1 = high_resolution_clock::now();

	std::thread t3(use_counter4, std::ref(c2));
	std::thread t4(use_counter4, std::ref(c2));

	t3.join();
	t4.join();
	time2 = high_resolution_clock::now();

	duration = duration_cast<microseconds> (time2 - time1).count();
	std::cout << "Duration (atomics): " << duration << "\n";
	std::cout << "Value (atomics): " << c.value() << "\n";

	
	return 0;
}