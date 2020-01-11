/**
 * @file /src/lib/standard_exception.cpp
 *
 * @brief Implementation for standard exceptions.
 *
 * @date April, 2009
 **/
/*****************************************************************************
** Disable check
*****************************************************************************/

#include <ecl/config/ecl.hpp>
#include <iostream>
#ifndef ECL_DISABLE_EXCEPTIONS

/*****************************************************************************
** Includes
*****************************************************************************/

#include "../../include/ecl/exceptions/standard_exception.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
 * Implementation [Standard Exception]
 ****************************************************************************/

StandardException::StandardException(const char* loc, ErrorFlag error ) :
    Exception(loc),
    error_flag(error)
{
    create_combined_message();
}

StandardException::StandardException(const char* loc, ErrorFlag error, const std::string &msg ) :
    Exception(loc),
    error_flag(error),
    detailed_message(msg)
{
    create_combined_message();
}

StandardException::StandardException(const char* loc, const StandardException &e ) :
    Exception(),
    error_flag(e.flag()),
    detailed_message(e.detailed_message)
{
    location = std::string(loc) + "\n         : " + e.location;
    create_combined_message();
}

void StandardException::create_combined_message() {
    this->combined_message = "\nLocation : " + this->location + "\n" + "Flag     : " + Error(error_flag).what() + "\n";
    if ( this->detailed_message.size() > 0 ) {
        combined_message  = combined_message + "Detail   : " + detailed_message + "\n";
    }
}
const char* StandardException::what() const throw() {

	return combined_message.c_str();
}

} // namespace ecl

#endif /* ECL_DISABLE_EXCEPTIONS */
