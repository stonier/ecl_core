/**
 * @file /src/lib/thread_win.cpp
 *
 * @brief Win32 thread implementation.
 *
 * @date April 2013
 **/
/*****************************************************************************
** Platform Check
*****************************************************************************/

#include <ecl/config/ecl.hpp>
#if defined(ECL_IS_WIN32)

/*****************************************************************************
** Includes
*****************************************************************************/

#include <functional>
#include <iostream>
#include <memory>
#include <thread>

#include <windows.h>

#include "../../include/ecl/threads/thread_win.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
* Thread Class Methods
*****************************************************************************/

Thread::Thread(VoidFunction function, const Priority &priority, const long &stack_size)
{
	start(function, priority, stack_size);
}

Error Thread::start(VoidFunction function, const Priority &priority, const long &)
{
	if (worker) {
		ecl_debug_throw(StandardException(LOC,BusyError,"The thread has already been started."));
		return Error(BusyError); // if in release mode, gracefully fall back to return values.
	}

	NullaryFreeFunction<void> nullary_function_object = generateFunctionObject(function);
	auto thread_task = std::make_shared<threads::ThreadTask<NullaryFreeFunction<void> > >(nullary_function_object, priority);
	try {
		// yield ownership of thread_task to new thread
		worker = std::make_unique<std::thread>(&threads::ThreadTask<NullaryFreeFunction<void> >::Execute, thread_task);
		thread_task.reset();
	}
	catch (...) {
		ecl_debug_throw(StandardException(LOC, UnknownError, "Failed to create thread."));
		return Error(UnknownError);
	}
	return setWorkerThreadPriority(priority);
}

Thread::~Thread() {
	cancel();
}

bool Thread::isRunning()
{
	DWORD exit_code = 0;
	if (worker && worker->native_handle() && ::GetExitCodeThread(worker->native_handle(), &exit_code)) {
		return (exit_code == STILL_ACTIVE);
	}
	return false;
}

void Thread::cancel() {
	if (!worker) {
		return;
	}

	DWORD exit_code = 0;
	if (worker->native_handle() && ::GetExitCodeThread(worker->native_handle(), &exit_code)) {
		if (exit_code == STILL_ACTIVE) {
			// unsafe termination.
			::TerminateThread(worker->native_handle(), exit_code);
		}
	}

	// this join() will not block since thread has either finished or has been terminated
	worker->join();
	worker.reset(nullptr);
}

void Thread::join() {
	if (worker->joinable()) {
		worker->join();
	}
}

Error Thread::setWorkerThreadPriority(const Priority &priority) {
	if (!worker) {
		// do nothing if no worker thread has been created
		return Error(NoError);
	}

	const auto& handle = worker->native_handle();
	BOOL bResult = FALSE;
	if (priority >= RealTimePriority1) {
		bResult = ::SetThreadPriority(handle, THREAD_PRIORITY_TIME_CRITICAL);
	}

	switch (priority) {
		case CriticalPriority:
			bResult = ::SetThreadPriority(handle, HIGH_PRIORITY_CLASS);
			break;
		case HighPriority:
			bResult = ::SetThreadPriority(handle, THREAD_PRIORITY_ABOVE_NORMAL);
			break;
		case LowPriority:
			bResult = ::SetThreadPriority(handle, THREAD_PRIORITY_BELOW_NORMAL);
			break;
		case BackgroundPriority:
			bResult = ::SetThreadPriority(handle, THREAD_PRIORITY_IDLE);
			break;
		default:
			break;
	}

	if (!bResult) {
		ecl_debug_throw(threads::throwPriorityException(LOC));
	}
	return Error(NoError);
}

}; // namespace ecl

#endif /* ECL_IS_WIN32 */
