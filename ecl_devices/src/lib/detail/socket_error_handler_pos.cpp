/**
 * @file /src/lib/detail/socket_error_handler_pos.cpp
 *
 * @brief Implements simple error handling for posix sockets.
 *
 * @date April 2009
 **/

/*****************************************************************************
** Cross platform
*****************************************************************************/

#include <ecl/config/ecl.hpp>
#ifndef ECL_IS_MAC
#ifdef ECL_IS_POSIX

/*****************************************************************************
** Includes
*****************************************************************************/

#include <errno.h>
#include <netdb.h> // gethostbyname
#include <ecl/errors/handlers.hpp>
#include "../../../include/ecl/devices/detail/socket_error_handler_pos.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {
namespace devices {

/*****************************************************************************
** Implementation [Exception Handlers]
*****************************************************************************/

ecl::Error socket_error(const char* loc) {
    switch( errno ) {
        case ( EACCES )     : return ecl::Error(ecl::OpenError);
        case ( EAFNOSUPPORT): return ecl::Error(ecl::NotSupportedError);
        case ( EINVAL )     : return ecl::Error(ecl::InvalidArgError);
        case ( EMFILE )     : return ecl::Error(ecl::OutOfRangeError);
        case ( ENFILE )     : return ecl::Error(ecl::OutOfResourcesError);
        case ( ENOBUFS )    : return ecl::Error(ecl::MemoryError);
        case ( ENOMEM )     : return ecl::Error(ecl::MemoryError);
        case ( EPROTONOSUPPORT )    : return ecl::Error(ecl::NotSupportedError);
		default             : return ecl::Error(UnknownError);
    }
}

ecl::Error bind_error(const char* loc) {
    switch( errno ) {
        case ( EACCES )     : return ecl::Error(ecl::PermissionsError);
        case ( EADDRINUSE ) : return ecl::Error(ecl::BusyError);
        case ( EBADF )      : return ecl::Error(ecl::InvalidObjectError);
        case ( EINVAL )     : return ecl::Error(ecl::BusyError);
        case ( ENOTSOCK )   : return ecl::Error(ecl::InvalidObjectError);
        case ( EADDRNOTAVAIL ) : return ecl::Error(ecl::InvalidObjectError);
        case ( EFAULT )     : return ecl::Error(ecl::OutOfRangeError);
        case ( ELOOP )      : return ecl::Error(ecl::SystemFailureError);
        case ( ENAMETOOLONG )  : return ecl::Error(ecl::InvalidArgError);
        case ( ENOENT )     : return ecl::Error(ecl::InvalidObjectError);
        case ( ENOMEM )     : return ecl::Error(ecl::MemoryError);
        case ( ENOTDIR )    : return ecl::Error(ecl::InvalidArgError);
        case ( EROFS )      : return ecl::Error(ecl::PermissionsError);
		default             : return ecl::Error(UnknownError);
    }
}

ecl::Error accept_error(const char* loc) {
    switch( errno ) {
		case ( EWOULDBLOCK ) : return ecl::Error(ecl::BlockingError);
		case ( EBADF )       : return ecl::Error(ecl::InvalidObjectError);
		case ( ECONNABORTED ): return ecl::Error(ecl::InterruptedError);
		case ( EINTR )       : return ecl::Error(ecl::InterruptedError);
		case ( EINVAL )      : return ecl::Error(ecl::UsageError);
		case ( EMFILE )      : return ecl::Error(ecl::OutOfResourcesError);
		case ( ENFILE )      : return ecl::Error(ecl::OutOfResourcesError);
		case ( ENOTSOCK )    : return ecl::Error(ecl::InvalidObjectError);
		case ( EOPNOTSUPP )  : return ecl::Error(ecl::InvalidObjectError);
		case ( EFAULT )      : return ecl::Error(ecl::PermissionsError);
		case ( ENOBUFS )     : return ecl::Error(ecl::MemoryError);
		case ( ENOMEM )      : return ecl::Error(ecl::MemoryError);
		case ( EPROTO )      : return ecl::Error(ecl::InvalidArgError);
		case ( EPERM )       : return ecl::Error(ecl::PermissionsError);
		default              : return ecl::Error(UnknownError);
    }
}

ecl::Error receive_error(const char* loc) {

    switch( errno ) {
		case ( EAGAIN || EWOULDBLOCK ) : return ecl::Error(ecl::InterruptedError);
		case ( EBADF       ) : return ecl::Error(ecl::InvalidObjectError);
		case ( ECONNREFUSED) : return ecl::Error(ecl::ConnectionError);
		case ( EFAULT      ) : return ecl::Error(ecl::SystemFailureError);
		case ( EINTR       ) : return ecl::Error(ecl::InterruptedError);
		case ( EINVAL      ) : return ecl::Error(ecl::InvalidArgError);
		case ( ENOMEM      ) : return ecl::Error(ecl::MemoryError);
		case ( ENOTCONN    ) : return ecl::Error(ecl::ConnectionError);
		case ( ENOTSOCK    ) : return ecl::Error(ecl::InvalidObjectError);
		default              : return ecl::Error(UnknownError);
    }
}

ecl::Error send_error(const char* loc) {

	switch( errno ) {
		case ( EAGAIN || EWOULDBLOCK ) : return ecl::Error(ecl::BlockingError);
		case ( EWOULDBLOCK ) : return ecl::Error(ecl::BlockingError);
		case ( EACCES      ) : return ecl::Error(ecl::PermissionsError);
		case ( EBADF       ) : return ecl::Error(ecl::InvalidObjectError);
		case ( ECONNRESET  ) : return ecl::Error(ecl::InterruptedError);
		case ( EFAULT      ) : return ecl::Error(ecl::SystemFailureError);
		case ( EINTR       ) : return ecl::Error(ecl::InterruptedError);
		case ( EINVAL      ) : return ecl::Error(ecl::InvalidArgError);
		case ( EISCONN     ) : return ecl::Error(ecl::ConnectionError);
		case ( EMSGSIZE    ) : return ecl::Error(ecl::WriteError);
		case ( ENOBUFS     ) : return ecl::Error(ecl::OutOfResourcesError);
		case ( ENOMEM      ) : return ecl::Error(ecl::MemoryError);
		case ( ENOTCONN    ) : return ecl::Error(ecl::ConnectionError);
		case ( ENOTSOCK    ) : return ecl::Error(ecl::InvalidObjectError);
		case ( EOPNOTSUPP  ) : return ecl::Error(ecl::NotSupportedError);
		case ( EPIPE       ) : return ecl::Error(ecl::InterruptedError);
		default              : return ecl::Error(UnknownError);
    }
}

ecl::Error ioctl_error(const char* loc) {

	switch( errno ) {
		case ( EBADF       ) : return ecl::Error(ecl::InvalidObjectError);
		case ( EFAULT      ) : return ecl::Error(ecl::OutOfRangeError);
		case ( EINVAL      ) : return ecl::Error(ecl::InvalidArgError);
		case ( ENOTTY      ) : return ecl::Error(ecl::InvalidObjectError);
		default              : return ecl::Error(UnknownError);
    }
}
ecl::Error gethostbyname_error() {
	switch( h_errno ) {
		case ( HOST_NOT_FOUND ) : return ecl::Error(ecl::ConnectionError);
		case ( NO_ADDRESS )  : return ecl::Error(ecl::InvalidArgError);
		case ( NO_RECOVERY ) : return ecl::Error(ecl::UnknownError);
		default              : return ecl::Error(ecl::UnknownError);
	}
}

ecl::Error connection_error(const char* loc) {
    switch( errno ) {
        case ( ( EACCES ) || ( EPERM ) ): return ecl::Error(ecl::PermissionsError);
        case ( EADDRINUSE )  : return ecl::Error(ecl::BusyError);
        case ( EAFNOSUPPORT ): return ecl::Error(ecl::NotSupportedError);
        case ( EAGAIN )      : return ecl::Error(ecl::OutOfResourcesError);
        case ( EALREADY )    : return ecl::Error(ecl::BlockingError);
        case ( EBADF )       : return ecl::Error(ecl::InvalidObjectError);
        case ( ECONNREFUSED ): return ecl::Error(ecl::ConnectionRefusedError);
        case ( EFAULT )      : return ecl::Error(ecl::OutOfRangeError);
        case ( EINPROGRESS ) : return ecl::Error(ecl::BlockingError);
        case ( EINTR )       : return ecl::Error(ecl::InterruptedError);
        case ( EISCONN )     : return ecl::Error(ecl::ConnectionError);
        case ( ENETUNREACH ) : return ecl::Error(ecl::ConfigurationError);
        case ( ENOTSOCK )    : return ecl::Error(ecl::InvalidObjectError);
        case ( ETIMEDOUT )   : return ecl::Error(ecl::TimeOutError);
		default              : return ecl::Error(ecl::UnknownError);
    }
}



} // namespace devices
} // namespace ecl

#endif  /* ECL_IS_POSIX */
#endif  /* !ECL_IS_MAC */

