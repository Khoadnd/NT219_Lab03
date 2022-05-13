#pragma once

#include <iostream>
#include <vector>
namespace Lab03 {
namespace big_int {
using size_t = unsigned long;
using byte = unsigned char;
using byte_arr = std::vector<byte>;
using std::size_t;
class unsigned_hex {
private:
  size_t _length;
  byte_arr _data;

public:
  unsigned_hex();
  unsigned_hex(size_t length);
  unsigned_hex(const unsigned_hex &other);
  ~unsigned_hex();

  void operator=(const unsigned_hex &other);
  unsigned_hex operator+(const unsigned_hex &other) const;
  unsigned_hex operator+(const unsigned &other) const;
  void operator+=(const unsigned_hex &other);
  void operator+=(const unsigned &other);

  unsigned_hex operator-(const unsigned_hex &other) const;
  unsigned_hex operator-(const unsigned &other) const;
  void operator-=(const unsigned_hex &other);
  void operator-=(const unsigned &other);

  unsigned_hex operator*(const unsigned_hex &other) const;
  unsigned_hex operator*(const unsigned &other) const;
  void operator*=(const unsigned_hex &other);
  void operator*=(const unsigned &other);

  unsigned_hex operator-() const;
  unsigned_hex operator~() const;

  // compare
  int operator<=>(const unsigned_hex &other) const;

  // in, out
  friend std::ostream &operator<<(std::ostream &os, const unsigned_hex &out);
  friend std::istream &operator>>(std::istream &is, unsigned_hex &in);

  // misc
  friend unsigned_hex int_to_hex(unsigned n);
};

unsigned_hex int_to_hex(unsigned n);

} // namespace big_int

} // namespace Lab03
