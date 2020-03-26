#include <list_processing/config/ExceptionHandler.hpp>

//
// ... Standard header files
//
#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <string>

namespace ListProcessing::Config
{
  ExceptionHandler::ExceptionHandler(int argc, char** argv)
    : exit_code(1)
  {
    try {
      std::rethrow_exception(std::current_exception());
    } catch (std::exception& e) {
      std::cerr << "list-processing-config encountered an unexpected exception:\n"
                << e.what() << std::endl;
      std::copy_n(
        argv, argc, std::ostream_iterator<std::string>(std::cerr << "Innvocation: ", " "));
    }
  }

  ExceptionHandler::operator int() const
  {
    return exit_code;
  }
} // end of namespace ListProcessing::Config
