#include <beard/containers/array.h>
#include <beard/containers/hash_map.h>
#include <beard/core/macros.h>
#include <beard/fmt/fmt.h>
#include <beard/misc/hash.h>
#include <beard/misc/timer.h>

#include <cassert>

int main() {
  beard::hash_map<i32, real> a;
  beard::string_hash_map<f64> b;
  beard::array<u32> c;

  constexpr u32 hash = beard::crc32::hash("Hello !");

  auto str = "12039813251203981";
  auto v = beard::fmt::parse_number<i64>(str);
  assert(v.has_value());
  assert(v.value() == 12039813251203981);
  assert(*v == 12039813251203981);

  str = "1230981 421809 102983 328190831025 2130598  340912812 098 321098 ";
  auto token_result = beard::fmt::tokenize(str, " ");
  assert(token_result.size() == 8);
  token_result = beard::fmt::tokenize(str, " ", false);
  assert(token_result.size() == 9);

  return 0;
}