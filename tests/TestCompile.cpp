#include <beard/core/macros.h>

#include <beard/containers/array.h>
#include <beard/containers/hash_map.h>
#include <beard/misc/hash.h>
#include <beard/misc/timer.h>

int main()
{
	beard::HashMap<i32, real> a;
	beard::StringHashMap<f64> b;
	beard::Array<u32>         c;

	constexpr u32 hash = beard::Crc32::Hash("Hello !");

	return 0;
}