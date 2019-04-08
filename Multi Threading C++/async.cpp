#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <map>

double get_price(const std::string & symbol)
{
	static const std::map<std::string, double> prices
	{
		{"GOOG", 100.0},
		{"IBM", 75.0},
		{"MSFT", 110.5},
		{"AABA", 63.2}
	};

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	auto item = prices.find(symbol);
	if (item != prices.end()) {
		return item->second;
	}
	else {
		throw std::invalid_argument("No such symbol");
	}
}

int main()
{
	std::cout << "Futures" << std::endl;

	auto symbol = "IBM";

	try {
		std::cout << "Getting price .. " << "\n";
		auto f = std::async(std::launch::async, get_price, symbol);

		std::cout << "In main ..." << std::endl;
		auto p = f.get();

		std::cout << "Price for " << symbol << " is " << p << std::endl;

	}
	catch (std::invalid_argument & ex) {
		std::cout << "Error ... " << symbol << ": " << ex.what() << "\n";
	}

	return 0;
}