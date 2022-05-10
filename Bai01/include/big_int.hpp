#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>

namespace Lab03 {
using std::ostream;
using uint_32bytes = boost::multiprecision::uint256_t;
using uint_8bytes = unsigned long long;
using uint_2bytes = unsigned short;

using random_generator_32 =
    boost::random::independent_bits_engine<boost::mt19937, 256,
                                           boost::multiprecision::uint256_t>;
using random_generator_8 =
    boost::random::independent_bits_engine<boost::mt19937, 32, uint_8bytes>;
using random_generator_2 =
    boost::random::independent_bits_engine<boost::mt19937, 8, uint_2bytes>;

static random_generator_32 gen32(time(nullptr) + 1);
static random_generator_8 gen8(time(nullptr) + 2);
static random_generator_2 gen2(time(nullptr) + 3);

} // namespace Lab03