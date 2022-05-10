#include "../include/prime.hpp"

namespace Lab03 {
namespace prime {

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