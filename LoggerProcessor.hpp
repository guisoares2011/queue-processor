#ifndef H_LOGGER_PROCESSOR
#define H_LOGGER_PROCESSOR

#include "QueueProcessor.hpp"
#include <string>

class LoggerProcessor : public QueueProcessor<std::string> {
	public:
		LoggerProcessor(MTHREAD::Mutex& paramMutext) : QueueProcessor(paramMutext) {}
		virtual ~LoggerProcessor(void) {}
	protected:
		void onProcess(int workerID, const std::string & data);
};

#endif // !H_LOGGER_PROCESSOR
