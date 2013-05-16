/**
 * @file /ecl_devices/src/lib/access.cpp
 *
 * @brief Implementation for access function to determine accessibility of a file
 *
 * @date May 2013
 **/

/*****************************************************************************
** Platform Check
*****************************************************************************/

#include <ecl/config.hpp>
#ifdef ECL_IS_WIN32

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ecl/exceptions/standard_exception.hpp>
#include "../../include/ecl/devices/access.hpp"

/*****************************************************************************
** Function Definition
*****************************************************************************/

int access(const char* path, int mode) {
    /******************************************
     * Parameter Checks
     ******************************************/
	/**
	 * checking path name
	 */
	if (!path || strlen(path) < 1)
		return -1;
	/**
	 * checking mode
	 */
	if ((mode & R_OK) != 0 &&
		(mode & W_OK) != 0 &&
		(mode & X_OK) != 0 &&
		(mode & F_OK) != 0)
		return -1;

    /******************************************
     * Accessibility Check
     ******************************************/
	DWORD dwDesiredAccess = 0;
	DWORD dwShareMode = 0;

	if (mode & R_OK) {
		dwDesiredAccess |= GENERIC_READ;
		dwShareMode |= FILE_SHARE_READ;
	}
	if (mode & W_OK) {
		dwDesiredAccess |= GENERIC_WRITE;
		dwShareMode |= FILE_SHARE_WRITE;
	}
	if (mode & X_OK) {
		dwDesiredAccess |= GENERIC_EXECUTE;
	}
	if (mode & F_OK) {
		dwDesiredAccess |= (FILE_READ_ATTRIBUTES | FILE_READ_DATA | FILE_READ_EA);
		dwShareMode |= FILE_SHARE_READ;
	}

	HANDLE hFile = CreateFile(path,
		dwDesiredAccess,
		dwShareMode,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		return -1;

	CloseHandle(hFile);
	return 0;
}

#endif // ECL_IS_WIN32
