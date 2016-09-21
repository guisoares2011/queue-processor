#ifndef __SCOPEDLOCK_HPP__
#define __SCOPEDLOCK_HPP__

#include <exception>
#include "Mutex.hpp"

namespace MTHREAD
{
	class ScopedLock
	{
		public:
			ScopedLock(Mutex& paramMtx) : mtx(paramMtx)
			{
				if (!mtx.isCreated()) throw std::exception("Mutex error");
				mtx.lock();
			}

			virtual ~ScopedLock()
			{
				mtx.unlock();
			}

		private:
			Mutex& mtx;
	};
};
#endif
