#include "include/big_int.hpp"
#include "include/big_int_helper.hpp"
#include <utility>
using Lab03::big_int::unsigned_hex;

#include <iostream>

int main() {
  unsigned_hex a, b;
  std::cin >> a >> b;
  std::cout << "a * b = " << a * b << std::endl;

  return 0;
}