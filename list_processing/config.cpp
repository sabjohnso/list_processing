//
// ... List Processing header files
//
#include <list_processing/config/Driver.hpp>
#include <list_processing/config/ExceptionHandler.hpp>

/**
 * @brief Return information related the configuration and build of the
 * List Processing Library
 *
 * @details The List Processing Library is a header only library, and
 * as such, the build and istallation does not have significant impact on
 * the usage.  However, there are some (1) configured parameters and there
 * is additional information that may be helpful to library users when
 * diagnosing bugs or performance issues.  This executable provides that
 * information.
 */
int
main(int argc, char** argv) {
  using ListProcessing::Config::Driver;
  using ListProcessing::Config::ExceptionHandler;
  try {
    return Driver(argc, argv);
  } catch (...) {
    return ExceptionHandler(argc, argv);
  }
}
