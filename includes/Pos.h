#include <string>
#ifndef POS_H
#define POS_H
struct Pos {//getter and setter
  Pos(const int& x, const int& y);
  Pos();
  int x; //up
  int y; //right
  const Pos operator+(const Pos& pos) const;
  const Pos operator-(const Pos& pos) const;
  const Pos scale(const int& scalar) const;
  const bool inRange(const Pos& min, const Pos& max) const;
  std::string show() const;

  const bool operator<(const Pos& other) const;
  const bool operator>(const Pos& other) const;
  const bool operator>=(const Pos& other) const;
  const bool operator==(const Pos& other) const;
  const Pos rotateRight() const;
  const Pos mirrorOnX() const;
};

#endif