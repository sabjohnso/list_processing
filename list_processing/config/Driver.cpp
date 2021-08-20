#include <list_processing/config/Driver.hpp>

namespace ListProcessing::Config {

  Driver::Driver(int, char**) {}

  Driver::operator int() const { return exit_code; }

} // end of namespace ListProcessing::Config
