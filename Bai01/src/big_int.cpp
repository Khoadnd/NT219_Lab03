#include "../include/big_int.hpp"
#include <algorithm>
#include <cctype>
#include <map>

namespace Lab03 {
namespace big_int {

static std::map<byte, unsigned> h_d{{'0', 0},  {'1', 1},  {'2', 2},  {'3', 3},
                                    {'4', 4},  {'5', 5},  {'6', 6},  {'7', 7},
                                    {'8', 8},  {'9', 9},  {'A', 10}, {'B', 11},
                                    {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}};

static std::map<unsigned, byte> d_h{{0, '0'},  {1, '1'},  {2, '2'},  {3, '3'},
                                    {4, '4'},  {5, '5'},  {6, '6'},  {7, '7'},
                                    {8, '8'},  {9, '9'},  {10, 'A'}, {11, 'B'},
                                    {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'}};

unsigned_hex::unsigned_hex() : _length(0) {}

unsigned_hex::unsigned_hex(size_t length) : _length(length) {
  _data.reserve(length);
}

unsigned_hex::unsigned_hex(const unsigned_hex &other) : _length(other._length) {
  _data.reserve(other._length);
  std::copy(other._data.begin(), other._data.end(), std::back_inserter(_data));
}

unsigned_hex::~unsigned_hex() {
  _data.clear();
  _data.resize(0);
  _data.shrink_to_fit();
}

unsigned_hex int_to_hex(unsigned n) {
  unsigned_hex result;
  result._data.reserve(sizeof(n));

  unsigned i = 0;
  while (n) {
    unsigned temp = 0;
    temp = n % 16;
    result._data.push_back(d_h[temp]);
    i++;
    n /= 16;
  }
  result._length = i;
  std::reverse(result._data.begin(), result._data.end());
  return result;
}

void unsigned_hex::operator=(const unsigned_hex &other) {
  if (this != &other) {
    _length = other._length;
    _data.clear();
    _data.reserve(other._length);
    std::copy(other._data.begin(), other._data.end(),
              std::back_inserter(_data));
  }
}

unsigned_hex unsigned_hex::operator+(const unsigned_hex &other) const {
  unsigned_hex result;
  result._length = std::max(_length, other._length);
  result._data.reserve(result._length);

  unsigned carry = 0;
  unsigned sum = 0;

  unsigned i, j;
  for (i = _length - 1, j = other._length - 1; i >= 0 || j >= 0; i--, j--) {
    sum = h_d[_data[i]] + h_d[other._data[j]] + carry;
    result._data.push_back(d_h[sum % 16]);
    carry = sum / 16;
  }

  while (i >= 0) {
    sum = h_d[_data[i]] + carry;
    result._data.push_back(d_h[sum % 16]);
    carry = sum / 16;
    i--;
  }

  while (j >= 0) {
    sum = h_d[other._data[j]] + carry;
    result._data.push_back(d_h[sum % 16]);
    carry = sum / 16;
    j--;
  }

  if (carry)
    result._data.push_back(d_h[carry]);

  std::reverse(result._data.begin(), result._data.end());
  result._length = result._data.size();
  return result;
}

void unsigned_hex::operator+=(const unsigned_hex &other) {
  *this = *this + other;
}

void unsigned_hex::operator+=(const unsigned &other) {
  *this = *this + int_to_hex(other);
}

unsigned_hex unsigned_hex::operator+(const unsigned &other) const {
  unsigned_hex temp = int_to_hex(other);
  return *this + temp;
}

unsigned_hex unsigned_hex::operator-(const unsigned_hex &other) const {
  unsigned_hex result;
  result._length = std::max(_length, other._length);
  result._data.reserve(result._length);

  unsigned borrow = 0;
  unsigned diff = 0;

  unsigned i, j;
  for (i = _length - 1, j = other._length - 1; i >= 0 || j >= 0; i--, j--) {
    diff = h_d[_data[i]] - h_d[other._data[j]] - borrow;
    if (diff < 0) {
      diff += 16;
      borrow = 1;
    } else {
      borrow = 0;
    }
    result._data.push_back(d_h[diff]);
  }

  while (i >= 0) {
    diff = h_d[_data[i]] - borrow;
    if (diff < 0) {
      diff += 16;
      borrow = 1;
    } else {
      borrow = 0;
    }
    result._data.push_back(d_h[diff]);
    i--;
  }

  while (j >= 0) {
    diff = h_d[other._data[j]] - borrow;
    if (diff < 0) {
      diff += 16;
      borrow = 1;
    } else {
      borrow = 0;
    }
    result._data.push_back(d_h[diff]);
    j--;
  }

  while (borrow) {
    diff = 16 - borrow;
    result._data.push_back(d_h[diff]);
    borrow = 0;
  }

  if (*this <=> other == -1)
    while (result._data.size() % 4 != 0)
      result._data.push_back('F');

  result._length = result._data.size();
  std::reverse(result._data.begin(), result._data.end());
  return result;
}

unsigned_hex unsigned_hex::operator-(const unsigned &other) const {
  unsigned_hex temp = int_to_hex(other);
  return *this - temp;
}

unsigned_hex unsigned_hex::operator-() const { // bu 2
  unsigned_hex result = ~*this;
  result = result + 1;

  std::reverse(result._data.begin(), result._data.end());
  while (result._length % 4 != 0) { // pad
    result._data.push_back('F');
    result._length++;
  }
  std::reverse(result._data.begin(), result._data.end());

  return result;
}

void unsigned_hex::operator-=(const unsigned_hex &other) {
  *this = *this - other;
}

void unsigned_hex::operator-=(const unsigned &other) {
  *this = *this - int_to_hex(other);
}

unsigned_hex unsigned_hex::operator*(const unsigned_hex &other) const {}

unsigned_hex unsigned_hex::operator~() const {
  unsigned_hex result;
  result._length = _length;
  result._data.reserve(_length);

  for (size_t i = 0; i < _length; i++)
    result._data.push_back(d_h[15 - h_d[_data[i]]]);

  return result;
}

int unsigned_hex::operator<=>(const unsigned_hex &other) const {
  if (_length > other._length)
    return 1;
  else if (_length < other._length)
    return -1;
  else
    for (size_t i = 0; i < _length; i++)
      if (h_d[_data[i]] > h_d[other._data[i]])
        return 1;
      else if (h_d[_data[i]] < h_d[other._data[i]])
        return -1;

  return 0;
}

std::ostream &operator<<(std::ostream &os, const unsigned_hex &out) {
  os << "0x";
  for (size_t i = 0; i < out._length; ++i)
    os << out._data[i];

  return os;
}

std::istream &operator>>(std::istream &is, unsigned_hex &in) {
  byte buffer = 0;
  if (is.peek() == '-')
    throw std::invalid_argument("Invalid input");

  if (is >> buffer, buffer == '0' && is.peek() == 'x') { // input as hex
    is.ignore();
    do {
      is >> buffer;
      if (buffer < '0' || tolower(buffer) > 'f' || buffer > '9' ||
          tolower(buffer) < 'a')
        throw std::invalid_argument("Invalid input");
      in._data.push_back(toupper(buffer));
    } while (is.peek() != '\n');
  } else // input as decimal, unimplemented
    throw std::invalid_argument("Invalid input");

  in._length = in._data.size();

  return is;
}

} // namespace big_int
} // namespace Lab03