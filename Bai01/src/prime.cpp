#include "../include/prime.hpp"
#include <boost/random/independent_bits.hpp>
#include <boost/random/mersenne_twister.hpp>

namespace Lab03 {
namespace prime {

uint_32bytes pow_mod(uint_32bytes base, uint_32bytes power, uint_32bytes mod) {
  if (power == 0)
    return 1;

  uint_32bytes y = 1;
  while (power > 1) {
    if (power % 2 == 0) {
      base = ((base % mod) * (base % mod)) % mod;
      power = power / 2;
    } else {
      y = (y * base) % mod;
      base = ((base % mod) * (base % mod)) % mod;
      power = (power - 1) / 2;
    }
  }
  return ((base % mod) * (y % mod)) % mod;
}

/*
euclid_extended(a,b):
x0 = 1, x1 = 0, y0 = 0, y1 = 1

while (b > 0)

r = a mod b; if r=0 then Break
q= a / b
x= x0-x1*q
y= y0-y1*q
a=b ; b=r ; x0=x1 ; x1=x ; y0=y1 ; y1=y

return x,y
*/

uint_32bytes gdc(uint_32bytes a, uint_32bytes b) {}

bool rabin_miller(uint_32bytes n, int round) {
  if (n == 2)
    return true;

  if (n == 1 || n % 2 == 0)
    return false;

  uint_32bytes bases[3] = {2, 7, 61};
  uint_32bytes q = n - 1;
  int k = 0;
  // n - 1 = 2 ^ k * q;
  while ((q & 1) == 0) {
    q >>= 1;
    k++;
  }

  using rng =
      boost::random::independent_bits_engine<boost::mt19937, 256, uint_32bytes>;
  rng gen(time(nullptr));
  uint_32bytes x = 0;
  for (int i = 0; i < round; ++i) {
    // uint_32bytes a = gen() % (n - 2); // gen random 2 <= a <= n - 2
    // a = a < 2 ? 2 : a;
    uint_32bytes a = std::min(n - 2, bases[i]);

    x = pow_mod(a, q, n);
    if (x == 1 || x == n - 1) // possible prime
      continue;

    int j;
    for (j = 1; j < k; j++) {
      x = pow_mod(x, 2, n);
      if (x == 1) // not prime
        return false;

      if (x == n - 1) // possible prime
        break;
    }
    if (j == k)
      return false;
  }
  return true;
}

uint_32bytes gen_odd_32() {
  while (true) {
    uint_32bytes tmp = gen32();
    if (tmp & 1)
      return tmp;
  }
}

uint_8bytes gen_odd_8() {
  while (true) {
    uint_8bytes tmp = gen8();
    if (tmp & 1)
      return tmp;
  }
}

uint_2bytes gen_odd_2() {
  while (true) {
    uint_2bytes tmp = gen2();
    if (tmp & 1)
      return tmp;
  }
}

} // namespace prime

} // namespace Lab03