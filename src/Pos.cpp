#include "Pos.h"
#include <string>

Pos::Pos(const int& xValue, const int& yValue)
    : x(xValue)
    , y(yValue)
{
}
Pos::Pos()
    : x(0)
    , y(0)
{
}

const Pos Pos::operator+(const Pos& position) const
{
  return Pos(x + position.x, y + position.y);
}

const Pos Pos::operator-(const Pos& position) const
{
  return Pos(position.x - x, position.y - y);
}

const Pos Pos::scale(const int& scalar) const
{
  return Pos(x * scalar, y * scalar);
}

const bool Pos::inRange(const Pos& min, const Pos& max) const
{
  if (*this >= min && *this < max) {
    return true;
  } else {
    return false;
  }
}

std::string Pos::show() const
{
  return std::string("(") + std::to_string(x) + ", " + std::to_string(y) + ")";
}

const bool Pos::operator<(const Pos& other) const
{
  if (x < other.x && y < other.y) {
    return true;
  } else {
    return false;
  }
}
const bool Pos::operator>(const Pos& other) const
{
  if (x > other.x && y > other.y) {
    return true;
  } else {
    return false;
  }
}

const bool Pos::operator>=(const Pos& other) const
{
  if (x >= other.x && y >= other.y) {
    return true;
  } else {
    return false;
  }
}

const bool Pos::operator==(const Pos& other) const
{
  if (x == other.x && y == other.y) {
    return true;
  } else {
    return false;
  }
}

//rotates vector 90 degrees to the right
const Pos Pos::rotateRight() const
{
  return Pos(this->y * -1, this->x);
}

//mirrors vector at x axis (the one going up)
const Pos Pos::mirrorOnX() const
{
  return Pos(this->x, this->y * -1);
}
