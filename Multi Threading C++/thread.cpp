#include <iostream>
#include <thread>
#include <chrono>


void func()
{
	auto id = std::this_thread::get_id();

	for (size_t i = 0; i < 5; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::cout << "[" << id << "] func executing" << "\n";
	}
}

void func2(char c, size_t interval)
{
	for (size_t i = 0; i < 10; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(interval));
		std::cout << c;
	}
}

void func3()
{
	for (size_t i = 0; i < 30; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::cout << "[" << std::this_thread::get_id() << "] func executing ....\n";
	}
}

int main1()
{
	std::cout << "Thread arguments" << std::endl;

	//auto id = std::this_thread::get_id();

	//std::cout << "[" << id << "] main executing" << "\n";

	//std::thread t1(func);
	//t1.detach();

	//std::thread t1([]() {
	//	auto id = std::this_thread::get_id();
	//	for (size_t i = 0; i < 10; i++)
	//	{
	//		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	//		std::cout << "[" << id << "] func executing" << "\n";
	//	}
	//});

	//std::thread t1(func2, 'a', 500);
	//std::thread t2(func2, 'A', 500);
	//std::thread t3(func2, '_', 500);
	
	//t1.join();
	//t2.join();
	//t3.join();

	//std::this_thread::sleep_for(std::chrono::milliseconds(1200));

	std::cout << "Threads and std::move" << std::endl;

	std::thread t1(func);
	std::cout << "main: started t1 \n";
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	std::thread t2 = std::move(t1);
	std::cout << "main: moved to t2 \n";

	std::cout << "t1 joinable " << t1.joinable() << "\n";
	std::cout << "t2 joinable " << t2.joinable() << "\n";

	t2.join();

	return 0;
}