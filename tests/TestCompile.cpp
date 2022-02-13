#include <beard/containers/array.h>
#include <beard/containers/hash_map.h>
#include <beard/core/macros.h>
#include <beard/misc/hash.h>
#include <beard/misc/timer.h>

int main() {
  beard::hash_map<i32, real> a;
  beard::string_hash_map<f64> b;
  beard::array<u32> c;

  constexpr u32 hash = beard::crc32::hash("Hello !");


	constexpr u32 hash = beard::Crc32::Hash("Hello !");

	return 0;
}