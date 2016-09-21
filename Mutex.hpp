#ifndef __MUTEX_HPP__
#define __MUTEX_HPP__

#include <cassert>
#include <Windows.h>

namespace MTHREAD
{
	class Mutex
	{
		public:
			Mutex(void) : hMtx(0)
			{
				hMtx = ::CreateMutex(0, FALSE, 0);
			}

			virtual ~Mutex()
			{
				if (hMtx) ::CloseHandle(hMtx);
			}

			void lock(void) const { assert(hMtx); ::WaitForSingleObject(hMtx, INFINITE); }
			void unlock(void) const { assert(hMtx); ::ReleaseMutex(hMtx); }

			bool isCreated(void) const { return hMtx != 0; }

		private:
			HANDLE hMtx;
	};
}

#endif
