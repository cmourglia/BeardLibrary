#include "beard/misc/timer.h"

#include <chrono>

namespace beard {
using Clock = std::chrono::high_resolution_clock;

timer::timer() { restart(); }

f64 timer::tick() {
  auto t = Clock::now();
  m_previous_tick = m_last_tick;
  m_last_tick = t.time_since_epoch().count();

  return delta_time();
}

void timer::restart() {
  auto t = Clock::now();
  m_start_time = t.time_since_epoch().count();
  m_last_tick = m_previous_tick = m_start_time;
}

u64 timer::delta_time_ns() const {
  u64 dt = m_last_tick - m_previous_tick;
  return dt;
}

u64 timer::delta_time_us() const { return delta_time_ns() / 1000; }

u64 timer::delta_time_ms() const { return delta_time_us() / 1000; }

f64 timer::delta_time() const {
  return static_cast<f64>(delta_time_ns()) * 1e-9;
}

f64 timer::time_since_start() const {
  u64 t = Clock::now().time_since_epoch().count();
  u64 dt = t - m_start_time;
  return static_cast<f64>(dt) * 1e-9;
}

}  // namespace beard