#pragma once

#include <beard/core/macros.h>
#include <math.h>
#include <stdio.h>

#include <glm/glm.hpp>
#include <numbers>

namespace beard {

// Math stuff
namespace float32 {
constexpr f32 Pi = std::numbers::pi_v<f32>;
constexpr f32 Pi_2 = Pi * 0.5f;
constexpr f32 Pi_3 = Pi / 3.0f;
constexpr f32 Pi_4 = Pi / 4.0f;
constexpr f32 Pi_6 = Pi / 6.0f;
constexpr f32 Pi_8 = Pi / 8.0f;
constexpr f32 Tau = Pi * 2.0f;

constexpr f32 DegToRad = Pi / 180.0f;
constexpr f32 RadToDeg = 180.0f / Pi;

constexpr f32 Sqrt_2 = std::numbers::sqrt2_v<f32>;
constexpr f32 E = std::numbers::e_v<f32>;
constexpr f32 Phi = std::numbers::phi_v<f32>;
}  // namespace float32

namespace float64 {
constexpr f64 Pi = std::numbers::pi_v<f64>;
constexpr f64 Pi_2 = Pi * 0.5;
constexpr f64 Pi_3 = Pi / 3.0;
constexpr f64 Pi_4 = Pi / 4.0;
constexpr f64 Pi_6 = Pi / 6.0;
constexpr f64 Pi_8 = Pi / 8.0;
constexpr f64 Tau = Pi * 2.0;

constexpr f64 DegToRad = Pi / 180.0;
constexpr f64 RadToDeg = 180.0 / Pi;

constexpr f64 Sqrt_2 = std::numbers::sqrt2_v<f64>;
constexpr f64 E = std::numbers::e_v<f64>;
constexpr f64 Phi = std::numbers::phi_v<f64>;
}  // namespace float64

// Alias Math with F32 of F64 depending on the Real type
#if defined(USE_DOUBLE)
namespace Math = F64;
#else
namespace math = float32;
#endif

namespace vec3 {
static constexpr glm::vec3 UP = {0.0f, 1.0f, 0.0f};
static constexpr glm::vec3 DOWN = {0.0f, -1.0f, 0.0f};
static constexpr glm::vec3 FRONT = {0.0f, 0.0f, 1.0f};
static constexpr glm::vec3 BACK = {0.0f, 0.0f, -1.0f};
static constexpr glm::vec3 RIGHT = {1.0f, 0.0f, 0.0f};
static constexpr glm::vec3 LEFT = {-1.0f, 0.0f, 0.0f};
}  // namespace vec3

// clang-format off
template <typename T> inline T min(const T a, const T b) { return a < b ? a : b; }
template <typename T> inline T max(const T a, const T b) { return a > b ? a : b; }
template <typename T> inline T clamp_bot(const T x, const T a) { return max(x, a); }
template <typename T> inline T clamp_top(const T x, const T a) { return min(x, a); }
template <typename T> inline T clamp(const T x, const T a, const T b) { return clamp_bot(a, clamp_top(x, b)); }
template <typename T> inline T saturate(const T x) { return clamp(x, T{0}, T{1}); }

template <typename T> inline T abs(const T x) { return abs(x); }
template <> inline f32 abs(const f32 x) { return fabsf(x); }
template <> inline f64 abs(const f64 x) { return fabs(x); }

inline f32 sin(const f32 x) { return std::sin(x); }
inline f32 cos(const f32 x) { return std::cos(x); }
inline f32 tan(const f32 x) { return std::tan(x); }
inline f32 asin(const f32 x) { return std::asin(x); }
inline f32 acos(const f32 x) { return std::acos(x); }
inline f32 atan(const f32 x) { return std::atan(x); }
inline f32 pow(const f32 x, const f32 e) { return std::pow(x, e); }
inline f32 sqrt(const f32 x) { return std::sqrt(x); }
inline f32 to_radians(const f32 x) { return x * float32::DegToRad; }
inline f32 to_degrees(const f32 x) { return x * float32::RadToDeg; }

inline f64 sin(const f64 x) { return std::sin(x); }
inline f64 cos(const f64 x) { return std::cos(x); }
inline f64 tan(const f64 x) { return std::tan(x); }
inline f64 asin(const f64 x) { return std::asin(x); }
inline f64 acos(const f64 x) { return std::acos(x); }
inline f64 atan(const f64 x) { return std::atan(x); }
inline f64 pow(const f64 x, const f64 e) { return std::pow(x, e); }
inline f64 sqrt(const f64 x) { return std::sqrt(x); }
inline f64 to_radians(const f64 x) { return x * float64::DegToRad; }
inline f64 to_degrees(const f64 x) { return x * float64::RadToDeg; }
// clang-format on

}  // namespace beard