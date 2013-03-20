/**
 * @file /include/ecl/sigslots/macros.hpp
 *
 * @brief Macros for error-checking and program termination.
 *
 * Macros for error-checking and program termination.
 *
 * @date April 2009.
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_SIGSLOTS_MACROS_HPP_
#define ECL_SIGSLOTS_MACROS_HPP_

/*****************************************************************************
** PreProcessing
*****************************************************************************/
/*
 * Import/exports symbols for the library
 */
#ifdef ECL_HAS_SHARED_LIBS // ecl is being built around shared libraries
  #ifdef ecl_sigslots_EXPORTS // we are building a shared lib/dll
    #define ecl_sigslots_PUBLIC ECL_HELPER_EXPORT
  #else // we are using shared lib/dll
    #define ecl_sigslots_PUBLIC ECL_HELPER_IMPORT
  #endif
  #define ecl_sigslots_LOCAL ECL_HELPERS_LOCAL
#else // ecl is being built around static libraries
  #define ecl_sigslots_PUBLIC
  #define ecl_sigslots_LOCAL
#endif


#endif /* ECL_SIGSLOTS_MACROS_HPP_*/
