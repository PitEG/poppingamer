#include "poppingamer/debug/logger.hpp"

#include <iostream>

namespace pg {
  void Logger::Print(std::string string) {
    std::cout << string;
  }

  void Logger::PrintLine(std::string string) {
    std::cout << string << std::endl;
  }
}
