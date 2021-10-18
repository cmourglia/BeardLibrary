#pragma once

#include <Beard/Macros.h>

#include <glm/glm.hpp>

#include <math.h>
#include <numbers>
#include <stdio.h>

namespace Beard
{

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

// Alias Math with F32 of F64 depending on the Real type
#if defined(USE_DOUBLE)
namespace Math = F64;
#else
namespace Math = F32;
#endif

namespace Vec3
{
	static constexpr glm::vec3 UP    = {0.0f, 1.0f, 0.0f};
	static constexpr glm::vec3 DOWN  = {0.0f, -1.0f, 0.0f};
	static constexpr glm::vec3 FRONT = {0.0f, 0.0f, 1.0f};
	static constexpr glm::vec3 BACK  = {0.0f, 0.0f, -1.0f};
	static constexpr glm::vec3 RIGHT = {1.0f, 0.0f, 0.0f};
	static constexpr glm::vec3 LEFT  = {-1.0f, 0.0f, 0.0f};
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

} // namespace Beard