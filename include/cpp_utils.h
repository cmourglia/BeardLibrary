#pragma once

// Macro helpers
#define global static
#define local static

#define COMPILER_MSVC 0
#define COMPILER_CLANG 0
#define COMPILER_GCC 0

// Clang is first to avoid problems with clang on windows
#if defined(__clang__)
#	undef COMPILER_CLANG
#	define COMPILER_CLANG (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#elif defined(_MSC_VER)
#	undef COMPILER_MSVC
#	define COMPILER_MSVC _MSC_VER
#elif defined(__GNUC__)
#	undef COMPILER_GCC
#	define COMPILER_GCC (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#	error "Undefined compiler"
#endif

#define PLATFORM_WINDOWS 0
#define PLATFORM_LINUX 0
#define PLATFORM_MACOS 0 // TODO

#if defined(_WIN32) || defined(_WIN64)
#	ifndef NOMINMAX
#		define NOMINMAX
#	endif
#	undef PLATFORM_WINDOWS
#	define PLATFORM_WINDOWS 1
#elif defined(__linux__)
#	undef PLATFORM_LINUX
#	define PLATFORM_LINUX 1
#else
#	error "Undefined platform"
#endif

#include <stdint.h>
#if UINTPTR_MAX == 0xffffffffffffffff
#	define ARCH64
#elif UINTPTR_MAX == 0xffffffff
#	define ARCH32
#else
#	error "Unsupported architecture"
#endif

#define DEBUG 0
#define RELWITHDEBINFO 0
#define RELEASE 0

#if defined(_DEBUG)
#	undef DEBUG
#	define DEBUG 1
#elif defined(_RELWITHDEBINFO)
#	undef RELWITHDEBINFO
#	define RELWITHDEBINFO 1
#else
#	undef RELEASE
#	define RELEASE 1
#endif

#define UNUSED(x) ((void)x)

#if COMPILER_GCC || COMPILER_CLANG
#	define ALIGN(x, a) x __attribute__((aligned(a))
#	define BREAKPOINT __asm__ volatile("int $0x03")
#	define LIKELY(x) __builtin_expect(!!(x), 1)
#elif COMPILER_MSVC
#	define ALIGN(x, a) __declspec(align(a)) x
#	define BREAKPOINT __debugbreak()
#	define LIKELY(x) (x)
#endif

// TODO: Add a message to the assert
#if DEBUG
#	define Assert(x)                                                                                                  \
		do                                                                                                             \
		{                                                                                                              \
			if (!LIKELY(x))                                                                                            \
			{                                                                                                          \
				BREAKPOINT;                                                                                            \
			}                                                                                                          \
		} while (false)
#else
#	define Assert(x)
#endif

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

// Types
using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using f32 = float;
using f64 = double;

// https://www.gingerbill.org/article/2015/08/19/defer-in-cpp
// clang-format off
template <typename Fn>
struct PrivDefer
{
	Fn fn;

	PrivDefer(Fn fn) : fn(fn) {}
	~PrivDefer() { fn(); }
};

template <typename Fn>
PrivDefer<Fn> DeferFunc(Fn fn) { return PrivDefer<Fn>(fn); }

#define DEFER_1(x, y) x##y
#define DEFER_2(x, y) DEFER_1(x, y)
#define DEFER_3(x) DEFER_2(x, __COUNTER__)
#define defer(code) auto DEFER_3(_defer_) = DeferFunc([&]() { code; })
// clang-format on

#include <stdio.h>
// Must call delete[] of the allocated buffer
inline const char* ReadFile(const char* filename)
{
	FILE* file = fopen(filename, "r");
	if (!file)
	{
		return nullptr;
	}
	defer(fclose(file));

	fseek(file, SEEK_SET, SEEK_END);
	long size = ftell(file);
	rewind(file);

	char*  buffer = new char[size];
	size_t read   = fread(buffer, 1, size, file);

	buffer[read] = '\0';

	return buffer;
}

#include <math.h>
// Math stuff
constexpr f32 PI   = 3.14159265359f;
constexpr f32 PI_2 = PI / 2.0f;
constexpr f32 PI_3 = PI / 3.0f;
constexpr f32 PI_4 = PI / 4.0f;
constexpr f32 PI_8 = PI / 8.0f;
constexpr f32 TAU  = 2.0f * PI;

constexpr f32 DEG_TO_RAD = PI / 180.0f;
constexpr f32 RAD_TO_DEG = 180.0f / PI;

constexpr f32 SQRT_2 = 1.41421356237f;
constexpr f32 E      = 2.71828182846f; // Euler's number
constexpr f32 PHI    = 1.61803398875f; // Golden ratio

// clang-format off
template <typename T> inline T Min(const T a, const T b) { return a < b ? a : b; }
template <typename T> inline T Max(const T a, const T b) { return a > b ? a : b; }
template <typename T> inline T ClampBot(const T x, const T a) { return Max(x, a); }
template <typename T> inline T ClampTop(const T x, const T a) { return Min(x, a); }
template <typename T> inline T Clamp(const T x, const T a, const T b) { return ClampBot(a, ClampTop(x, b)); }
template <typename T> inline T Saturate(const T x) { return Clamp(x, T{0}, T{1}); }

inline f32 Sine(const f32 x) { return sinf(x); }
inline f32 Cosine(const f32 x) { return cosf(x); }
inline f32 Tangent(const f32 x) { return tanf(x); }
inline f32 ArcSine(const f32 x) { return asinf(x); }
inline f32 ArcCosine(const f32 x) { return acosf(x); }
inline f32 ArcTangent(const f32 x) { return atanf(x); }

inline f32 Pow(const f32 x, const f32 e) { return powf(x, e); }
inline f32 Sqrt(const f32 x) { return sqrtf(x); }

inline f32 ToRadians(f32 x) { return x * DEG_TO_RAD; }
inline f32 ToDegrees(f32 x) { return x * RAD_TO_DEG; }
// clang-format on