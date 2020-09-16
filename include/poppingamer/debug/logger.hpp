#include <string>

namespace pg {
  class Logger {
  public:
    static void Print(std::string string);
    static void PrintLine(std::string string);
  };
}

