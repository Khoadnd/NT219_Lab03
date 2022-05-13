#include "include/big_int.hpp"
using Lab03::big_int::unsigned_hex;

#include <iostream>

int main() {
  unsigned_hex a;
  std::cin >> a;
  std::cout << a + 12343 << std::endl;
  return 0;
}