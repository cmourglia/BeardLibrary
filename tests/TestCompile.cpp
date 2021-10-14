#include <Beard/Macros.h>

#include <Beard/Array.h>
#include <Beard/Hash.h>
#include <Beard/HashMap.h>
#include <Beard/Timer.h>

int main()
{
	Beard::HashMap<i32, real> a;
	Beard::StringHashMap<f64> b;
	Beard::Array<u32>         c;

	constexpr u32 hash = Beard::Crc32::Hash("Hello !");

	return 0;
}