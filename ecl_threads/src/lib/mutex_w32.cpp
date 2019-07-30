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

#include <windows.h>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
* Mutex Class Methods
*****************************************************************************/

Mutex::Mutex(const bool locked) : number_locks(0)  {
    if (locked) {
        this->mutex.lock();
    }
}

void Mutex::lock() {
    long n = number_locks;
    InterlockedIncrement(&n);
    number_locks = n;

    this->mutex.lock();
}

bool Mutex::trylock(Duration&) {
    return trylock();
}

bool Mutex::trylock() {
    if (number_locks) {
        return false;
    }
    lock();
    return true;
}

void Mutex::unlock()
{
    this->mutex.unlock();

    long n = number_locks;
    InterlockedDecrement(&n);
    number_locks = n;
}

} // namespace ecl

#endif /* ECL_IS_WIN32 */
