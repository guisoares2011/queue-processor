#include "LoggerProcessor.hpp"
#include <iostream>
#include <thread>
#include <string>
#include <windows.h>

using namespace std;

LoggerProcessor* broker;

void createWorkers() {
	broker->start(5);
}

void addMessagesToQueue()
{
	for (DWORD i = 0; i < 10000000; i++) {
		broker->push("Test");
	}

	while (!broker->empty()) {
		Sleep(1);
	}
	broker->stop();
}


int main() {
	broker = new LoggerProcessor();
	//std::thread frist(createWorkers);
	std::thread second(addMessagesToQueue);
	// spawn new thread that calls foo()
	  // spawn new thread that calls bar(0)

	std::cout << "main, foo and bar now execute concurrently...\n";
	broker->start(2);
	second.join();

	std::cout << "foo and bar completed.\n";
	return 0;
}