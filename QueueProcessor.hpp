#ifndef H_BROKER_MESSAGE
#define H_BROKER_MESSAGE

#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <thread>
#include <Windows.h>
#include <queue>
#include <mutex> 
using namespace std;

template <class T>
class QueueProcessor {
	private:
		bool alive = 0;
		std::vector<thread*> workers = {};
		std::queue<T> queue;
		std::mutex mtx;
		void createWorkers(int pool);
	protected:
		void virtual onProcess(int workerID, T const&) = 0;
	public:
		QueueProcessor() {};
		~QueueProcessor() {
			this->stop();
			cout << "Finished!" << endl;
		};
		void stop();
		void start(int pool);
		void push(T const& data);
		void onPeek(int i);	
		bool isAlive() { return alive; }
		bool empty() const {  return queue.empty(); }
};

template<class T>
inline void QueueProcessor<T>::stop()
{
	alive = 0;
}

template<class T>
inline void QueueProcessor<T>::createWorkers(int pool)
{
	for (int i = 0; i < pool; i++) {
		workers.push_back(new thread(&QueueProcessor::onPeek, this, i));
	}

	for (std::size_t w = 0; w < workers.size(); w++) {
		workers.at(w)->join();
	}
}

template<class T>
inline void QueueProcessor<T>::start(int pool = 1)
{
	cout << "Start ..." << endl;
	if (!this->alive) {
		this->alive = true;
		this->createWorkers(pool);
	}
}

template<class T>
inline void QueueProcessor<T>::push(T const & data)
{
	queue.push(data);
}

template<class T>
inline void QueueProcessor<T>::onPeek(int workerID)
{
	while (this->isAlive()) {
		//cout << "Worker " << i << endl;
		
		if (!queue.empty()) {
			mtx.lock();
			T const& _tmp = queue.front();
			queue.pop();
			this->onProcess(workerID, _tmp);
			mtx.unlock();
		}
		

		Sleep(10);
	}
}
#endif // !H_BROKER_MESSAGE