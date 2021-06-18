#pragma once

// Macro helpers
#define global_variable static
#define local_variable static

#define Z_COMPILER_MSVC 0
#define Z_COMPILER_CLANG 0
#define Z_COMPILER_GCC 0

// Clang is first to avoid problems with clang on windows
#if defined(__clang__)
#	undef Z_COMPILER_CLANG
#	define Z_COMPILER_CLANG (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#elif defined(_MSC_VER)
#	undef Z_COMPILER_MSVC
#	define Z_COMPILER_MSVC _MSC_VER
#elif defined(__GNUC__)
#	undef Z_COMPILER_GCC
#	define Z_COMPILER_GCC (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#	error "Undefined compiler"
#endif

#define Z_PLATFORM_WINDOWS 0
#define Z_PLATFORM_LINUX 0
#define Z_PLATFORM_MACOS 0 // TODO

#if defined(_WIN32) || defined(_WIN64)
#	ifndef NOMINMAX
#		define NOMINMAX
#	endif
#	undef Z_PLATFORM_WINDOWS
#	define Z_PLATFORM_WINDOWS 1
#elif defined(__linux__)
#	undef Z_PLATFORM_LINUX
#	define Z_PLATFORM_LINUX 1
#else
#	error "Undefined platform"
#endif

#include <stdint.h>
#if UINTPTR_MAX == 0xffffffffffffffff
#	define Z_ARCH64
#elif UINTPTR_MAX == 0xffffffff
#	define Z_ARCH32
#else
#	error "Unsupported architecture"
#endif

#define Z_DEBUG 0
#define Z_RELWITHDEBINFO 0
#define Z_RELEASE 0

#if defined(_DEBUG)
#	undef Z_DEBUG
#	define Z_DEBUG 1
#elif defined(_RELWITHDEBINFO)
#	undef Z_RELWITHDEBINFO
#	define Z_RELWITHDEBINFO 1
#else
#	undef Z_RELEASE
#	define Z_RELEASE 1
#endif

#define Z_UNUSED(x) ((void)x)

#if Z_COMPILER_GCC || Z_COMPILER_CLANG
#	define Z_ALIGN(x, a) x __attribute__((aligned(a))
#	define Z_BREAKPOINT __asm__ volatile("int $0x03")
#	define Z_LIKELY(x) __builtin_expect(!!(x), 1)
#	define Z_NO_VTABLE
#elif Z_COMPILER_MSVC
#	define Z_ALIGN(x, a) __declspec(align(a)) x
#	define Z_BREAKPOINT __debugbreak()
#	define Z_LIKELY(x) (x)
#	define Z_NO_VTABLE __declspec(novtable)
#endif

// TODO: Add a message to the assert
#if Z_DEBUG
#	define Assert(x)                                                                                                  \
		do                                                                                                             \
		{                                                                                                              \
			if (!Z_LIKELY(x))                                                                                          \
			{                                                                                                          \
				Z_BREAKPOINT;                                                                                          \
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

using isize = intptr_t;
using usize = uintptr_t;

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
#include <numbers>

// Math stuff
namespace F32
{
constexpr f32 Pi   = std::numbers::pi_v<f32>;
constexpr f32 Pi_2 = Pi * 0.5f;
constexpr f32 Pi_3 = Pi / 3.0f;
constexpr f32 Pi_4 = Pi / 4.0f;
constexpr f32 Pi_6 = Pi / 6.0f;
constexpr f32 Pi_8 = Pi / 8.0f;
constexpr f32 Tau  = Pi * 2.0f;

constexpr f32 DegToRad = Pi / 180.0f;
constexpr f32 RadToDeg = 180.0f / Pi;

constexpr f32 Sqrt_2 = std::numbers::sqrt2_v<f32>;
constexpr f32 E      = std::numbers::e_v<f32>;
constexpr f32 Phi    = std::numbers::phi_v<f32>;
}

namespace F64
{
constexpr f64 Pi   = std::numbers::pi_v<f64>;
constexpr f64 Pi_2 = Pi * 0.5;
constexpr f64 Pi_3 = Pi / 3.0;
constexpr f64 Pi_4 = Pi / 4.0;
constexpr f64 Pi_6 = Pi / 6.0;
constexpr f64 Pi_8 = Pi / 8.0;
constexpr f64 Tau  = Pi * 2.0;

constexpr f64 DegToRad = Pi / 180.0;
constexpr f64 RadToDeg = 180.0 / Pi;

constexpr f64 Sqrt_2 = std::numbers::sqrt2_v<f64>;
constexpr f64 E      = std::numbers::e_v<f64>;
constexpr f64 Phi    = std::numbers::phi_v<f64>;
}

// clang-format off
template <typename T> inline T Min(const T a, const T b) { return a < b ? a : b; }
template <typename T> inline T Max(const T a, const T b) { return a > b ? a : b; }
template <typename T> inline T ClampBot(const T x, const T a) { return Max(x, a); }
template <typename T> inline T ClampTop(const T x, const T a) { return Min(x, a); }
template <typename T> inline T Clamp(const T x, const T a, const T b) { return ClampBot(a, ClampTop(x, b)); }
template <typename T> inline T Saturate(const T x) { return Clamp(x, T{0}, T{1}); }

template <typename T> inline T Abs(const T x) { return abs(x); }
template <> inline f32 Abs(const f32 x) { return fabsf(x); }
template <> inline f64 Abs(const f64 x) { return fabs(x); }

inline f32 Sine(const f32 x) { return sinf(x); }
inline f32 Cosine(const f32 x) { return cosf(x); }
inline f32 Tangent(const f32 x) { return tanf(x); }
inline f32 ArcSine(const f32 x) { return asinf(x); }
inline f32 ArcCosine(const f32 x) { return acosf(x); }
inline f32 ArcTangent(const f32 x) { return atanf(x); }
inline f32 Pow(const f32 x, const f32 e) { return powf(x, e); }
inline f32 Sqrt(const f32 x) { return sqrtf(x); }
inline f32 ToRadians(const f32 x) { return x * F32::DegToRad; }
inline f32 ToDegrees(const f32 x) { return x * F32::RadToDeg; }

inline f64 Sine(const f64 x) { return sin(x); }
inline f64 Cosine(const f64 x) { return cos(x); }
inline f64 Tangent(const f64 x) { return tan(x); }
inline f64 ArcSine(const f64 x) { return asin(x); }
inline f64 ArcCosine(const f64 x) { return acos(x); }
inline f64 ArcTangent(const f64 x) { return atan(x); }
inline f64 Pow(const f64 x, const f64 e) { return pow(x, e); }
inline f64 Sqrt(const f64 x) { return sqrt(x); }
inline f64 ToRadians(const f64 x) { return x * F64::DegToRad; }
inline f64 ToDegrees(const f64 x) { return x * F64::RadToDeg; }
// clang-format on