#include <boost/multiprecision/cpp_int.hpp>
using big_int = boost::multiprecision::uint256_t;

#include <iostream>
using std::cin;
using std::cout;

big_int mod_inverse(big_int n, big_int mod) {
  big_int y0 = 0, y1 = 1;
  big_int r, q, d;
  while (n > 0) {
    r = mod % n;
    if (r == 0)
      break;

    q = mod / n;

    d = y0 - y1 * q;
    mod = n;
    n = r;
    y0 = y1;
    y1 = d;
  }

  return d;
}

big_int pow_mod(big_int base, big_int power, big_int mod) {
  if (power == 0)
    return 1;

  big_int result = 1;
  base %= power;

  if (base == 0)
    return 0;

  while (power > 0) {
    if (power & 1)
      result = (result * base) % power;

    power >>= 1;
    base = (base * base) % power;
  }
  return result;
}

int main() {
  big_int p, q, e, n, phi, d;
  cout << "Enter valid p: ";
  cin >> p;
  cout << "Enter valid q: ";
  cin >> q;
  cout << "Enter valid e: ";
  cin >> e;

  n = p * q;
  phi = (p - 1) * (q - 1);

  // d = e ^ - 1 mod phi
  d = mod_inverse(e, phi);

  cout << "n = " << n << std::endl;
  cout << "phi = " << phi << std::endl;
  cout << "d = " << d << std::endl;

  cout << "Your public key is: (" << e << ", " << n << ")" << std::endl;
  cout << "Your private key is: (" << d << ", " << n << ")" << std::endl;

  big_int message;
  cout << "Enter message: ";
  cin >> message;

  big_int cipher = pow_mod(message, e, n);
  cout << "C = E(M, PU) = " << cipher << std::endl;
  cout << "Recovered: " << pow_mod(cipher, d, n) << std::endl;
}