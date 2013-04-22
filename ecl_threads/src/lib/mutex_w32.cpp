/**
 * @file /ecl_threads/src/lib/mutex_w32.cpp
 *
 * @brief Win32 mutex implementation.
 *
 * @date May 2010
 **/
/*****************************************************************************
** Platform Check
*****************************************************************************/

#include <ecl/config/ecl.hpp>
#if defined(ECL_IS_WIN32)

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ecl/exceptions/standard_exception.hpp>
#include "../../include/ecl/threads/mutex_w32.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
* Mutex Class Methods
*****************************************************************************/

Mutex::Mutex(const bool locked) : number_locks(0)  {

	InitializeCriticalSection(&mutex); // has no return value
	if ( locked ) {
		this->lock();
	}
};

Mutex::~Mutex() {
	DeleteCriticalSection(&mutex); // has no return value
}

void Mutex::lock() {
    ++number_locks;
    EnterCriticalSection(&mutex); // has no return value
};

bool Mutex::trylock(Duration &duration) {
	return trylock();
};

bool Mutex::trylock() {
	int result = TryEnterCriticalSection(&mutex);
	if ( result == 0 ) {
		return false;
	} else {
		++number_locks;
		return true;
	}
};


void Mutex::unlock()
{
    --number_locks;
    LeaveCriticalSection( &mutex );
};

}; // namespace ecl

#endif /* ECL_IS_WIN32 */
