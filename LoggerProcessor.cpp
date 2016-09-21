#include "LoggerProcessor.hpp"
#include <iostream>
#include <Windows.h>
void LoggerProcessor::onProcess(int workerID, const std::string& data)
{
	//std::cout << workerID << " : " << data << " ; " << std::endl;
	Sleep(2000);
};
