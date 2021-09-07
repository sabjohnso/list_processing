#pragma once

namespace ListProcessing::Config {
  class ExceptionHandler
  {
  public:
    ExceptionHandler(int argc, char** argv);

    operator int() const;

  private:
    int exit_code;
  };
} // end of namespace ListProcessing::Config
