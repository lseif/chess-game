#include "Exceptions.h"

NotAllowedMoveException::NotAllowedMoveException(const char* massage)
    : std::runtime_error(massage)
    , massage(massage)
{
}

const char* NotAllowedMoveException::what()
{
  return massage;
}