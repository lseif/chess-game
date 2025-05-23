#include "Pos.h"
#include <stdexcept>

class NotAllowedMoveException : public std::runtime_error {
  public:
  const char* massage;
  NotAllowedMoveException(const char* massage);
  virtual const char* what();
};
