#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>


class Counter2
{
	mutable std::atomic_long val;
public:
	Counter2( ) : val{} {}
	Counter2(long initial) : val(initial) {}
	void increment() { val++; }
	long value() const { return val.load(); }
};

void use_counter2(Counter2 &c)
{
	for (size_t i = 0; i < 100; i++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		c.increment();
		std::cout << c.value() << "\n";
	}
}

int main3()
{
	Counter2 c2;
	std::cout << "Counter using atomics" << std::endl;

	std::thread t3(use_counter2, std::ref(c2));
	std::thread t4(use_counter2, std::ref(c2));

	t3.join();
	t4.join();
	return 0;
}