#include "LoggerProcessor.hpp"
#include <iostream>
#include <thread>
#include <string>
#include <windows.h>
#include "Mutex.hpp"
using namespace std;

LoggerProcessor* broker;
MTHREAD::Mutex mtx;

void addMessagesToQueue()
{
	mtx.lock();
	for (DWORD i = 0; i < 1000000; i++) { broker->push("Test"); }
	mtx.unlock();
	while (!broker->empty()) {
		Sleep(1);
	}
	std::cout << "FinishedDDDD!" << endl;
	broker->stop();
}


int main() {
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	int numCPU = sysinfo.dwNumberOfProcessors;

	broker = new LoggerProcessor(mtx);
	//std::thread frist(createWorkers);
	std::thread second(addMessagesToQueue);
	broker->start(numCPU * 40);
	second.join();
	return 0;
}