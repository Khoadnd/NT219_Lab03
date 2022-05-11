#include "include/big_int.hpp"
#include "include/prime.hpp"
#include <iostream>
#include <thread>

static bool found = false;

void find() {
  using std::cout;
  Lab03::uint_32bytes n = Lab03::prime::gen_odd_32();
  while (found = Lab03::prime::rabin_miller(n, 3), !found) {
    cout << "testing " << n << "..." << std::endl;
    n = Lab03::prime::gen_odd_32();
  }
  cout << n << " is prime";
}

int main() {
  std::thread a(find);
  a.join();

  return 0;
}