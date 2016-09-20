#ifndef H_LOGGER_PROCESSOR
#define H_LOGGER_PROCESSOR

#include "QueueProcessor.hpp"
#include <string>

class LoggerProcessor : public QueueProcessor<std::string> {
	public:
		LoggerProcessor() : QueueProcessor() {
			
		}
		virtual ~LoggerProcessor(void) {}
	protected:
		void onProcess(int workerID, std::string const & data);
};

#endif // !H_LOGGER_PROCESSOR
