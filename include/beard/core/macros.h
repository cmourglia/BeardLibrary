#pragma once

// Macro helpers
#define global_variable static
#define local_variable static

#define BEARD_COMPILER_MSVC 0
#define BEARD_COMPILER_CLANG 0
#define BEARD_COMPILER_GCC 0

// Clang is first to avoid problems with clang on windows
#if defined(__clang__)
#	undef BEARD_COMPILER_CLANG
#	define BEARD_COMPILER_CLANG (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#elif defined(_MSC_VER)
#	undef BEARD_COMPILER_MSVC
#	define BEARD_COMPILER_MSVC _MSC_VER
#elif defined(__GNUC__)
#	undef BEARD_COMPILER_GCC
#	define BEARD_COMPILER_GCC (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#	error "Undefined compiler"
#endif

#define BEARD_PLATFORM_WINDOWS 0
#define BEARD_PLATFORM_LINUX 0
#define BEARD_PLATFORM_MACOS 0 // TODO

#if defined(_WIN32) || defined(_WIN64)
#	ifndef NOMINMAX
#		define NOMINMAX
#	endif
#	undef BEARD_PLATFORM_WINDOWS
#	define BEARD_PLATFORM_WINDOWS 1
#elif defined(__linux__)
#	undef BEARD_PLATFORM_LINUX
#	define BEARD_PLATFORM_LINUX 1
#else
#	error "Undefined platform"
#endif

#include <stdint.h>
#if UINTPTR_MAX == 0xffffffffffffffff
#	define BEARD_ARCH64
#elif UINTPTR_MAX == 0xffffffff
#	define BEARD_ARCH32
#else
#	error "Unsupported architecture"
#endif

#define BEARD_DEBUG 0
#define BEARD_RELWITHDEBINFO 0
#define BEARD_RELEASE 0

#if defined(_DEBUG)
#	undef BEARD_DEBUG
#	define BEARD_DEBUG 1
#elif defined(_RELWITHDEBINFO)
#	undef BEARD_RELWITHDEBINFO
#	define BEARD_RELWITHDEBINFO 1
#else
#	undef BEARD_RELEASE
#	define BEARD_RELEASE 1
#endif

#define BEARD_UNUSED(x) ((void)x)

#if BEARD_COMPILER_GCC || BEARD_COMPILER_CLANG
#	define BEARD_ALIGN(x, a) x __attribute__((aligned(a))
#	define BEARD_BREAKPOINT __asm__ volatile("int $0x03")
#	define BEARD_LIKELY(x) __builtin_expect(!!(x), 1)
#	define BEARD_NO_VTABLE
#elif BEARD_COMPILER_MSVC
#	define BEARD_ALIGN(x, a) __declspec(align(a)) x
#	define BEARD_BREAKPOINT __debugbreak()
#	define BEARD_LIKELY(x) (x)
#	define BEARD_NO_VTABLE __declspec(novtable)
#endif

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

#define BEARD_STRINGIFY(x) #x
#define BEARD_TOSTRING(x) BEARD_STRINGIFY(x)
#define BEARD_AT __FILE__ ":" BEARD_TOSTRING(__LINE__)

#define BEARD_TODO(...) __pragma(message("TODO at " BEARD_AT " -> " __VA_ARGS__))

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

#if defined(USE_DOUBLE)
using real = f64;
#else
using real = f32;
#endif

template <typename T>
inline constexpr T KB(T x) {
  return T{1024} * x;
}

template <typename T>
inline constexpr T MB(T x) {
  return T{1024} * KB(x);
}

template <typename T>
inline constexpr T GB(T x) {
  return T{1024} * MB(x);
}

template <typename T>
inline constexpr T TB(T x) {
  return T{1024} * GB(x);
}

template <typename T>
inline constexpr T KiB(T x) {
  return T{1000} * x;
}

template <typename T>
inline constexpr T MiB(T x) {
  return T{1000} * KiB(x);
}

template <typename T>
inline constexpr T GiB(T x) {
  return T{1000} * MiB(x);
}

template <typename T>
inline constexpr T TiB(T x) {
  return T{1000} * GiB(x);
}

#define UNUSED(x) (void)(x)

#define NONCOPYABLE(T)                                                                                                 \
	T(const T&)  = delete;                                                                                             \
	void operator=(const T&) = delete
#define NONMOVEABLE(T)                                                                                                 \
	T(T&&) noexcept = delete;                                                                                          \
	void operator=(T&&) noexcept = delete

#define DEFAULT_COPYABLE(T)                                                                                            \
	T(const T&) = default;                                                                                             \
	T& operator=(const T&) = default

#define DEFAULT_MOVEABLE(T)                                                                                            \
	T(T&&) noexcept = default;                                                                                         \
	T& operator=(T&&) noexcept = default

#define DEFAULT_CTORS(T)                                                                                               \
	DEFAULT_COPYABLE(T);                                                                                               \
	DEFAULT_MOVEABLE(T)

#if BEARD_PLATFORM_WINDOWS
#	define DEBUGBREAK __debugbreak()
#else
// TODO: Handle other cases
#	define DEBUGBREAK                                                                                                 \
		int* trap = reinterpret_cast<int*>(3L);                                                                        \
		*trap     = 3
#endif

#if BEARD_PLATFORM_WINDOWS
#	define START_EXTERNAL_INCLUDE __pragma(warning(push)) __pragma(warning(disable : 4201))
#	define END_EXTERNAL_INCLUDE __pragma(warning(pop))

#	define VARIABLE_LENGTH_ARRAY(type, name)                                                                          \
		__pragma(warning(push));                                                                                       \
		__pragma(warning(disable : 4200));                                                                             \
		type name[0];                                                                                                  \
		__pragma(warning(pop))
#else
#	define START_EXTERNAL_INCLUDE
#	define END_EXTERNAL_INCLUDE

#	define VARIABLE_LENGTH_ARRAY(type, name) type name[]
#endif

#define NOOP(...)

#ifdef _DEBUG
#	define ASSERT(x, msg, ...)                                                                                        \
		__pragma(warning(push));                                                                                       \
		__pragma(warning(disable : 4002));                                                                             \
		if (!(x))                                                                                                      \
		{                                                                                                              \
			fprintf(stderr, "Assertion `%s` failed (%s:%d): \"" msg "\"", #x, __FILE__, __LINE__, __VA_ARGS__);        \
			DEBUGBREAK;                                                                                                \
		}                                                                                                              \
		__pragma(warning(pop))

#	define ASSERT_UNREACHABLE() ASSERT(false, "Unreachable path")
#else
#	define ASSERT(x) NOOP(x)
#	define ASSERT_UNREACHABLE() NOOP()
#endif

// https://www.gingerbill.org/article/2015/08/19/defer-in-cpp
// clang-format off
namespace Priv
{
template <typename Fn>
struct PrivDefer
{
	Fn fn;

	PrivDefer(Fn fn) : fn(fn) {}
	~PrivDefer() { fn(); }
};

template <typename Fn>
PrivDefer<Fn> DeferFunc(Fn fn) { return PrivDefer<Fn>(fn); }
}

#define DEFER_1(x, y) x##y
#define DEFER_2(x, y) DEFER_1(x, y)
#define DEFER_3(x) DEFER_2(x, __COUNTER__)
#define defer(code) auto DEFER_3(_defer_) = Priv::DeferFunc([&]() { code; })
// clang-format on

#define TODO throw std::exception("TODO")