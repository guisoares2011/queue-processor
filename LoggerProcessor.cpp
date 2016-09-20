#include "LoggerProcessor.hpp"
#include <iostream>

void LoggerProcessor::onProcess(int workerID, const std::string & data)
{
	std::cout << "Proccessing : " << workerID << " : " << data << " ; " << std::endl;
};
