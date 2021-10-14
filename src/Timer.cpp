#include <Beard/Timer.h>

#include <chrono>

namespace Beard
{
using Clock = std::chrono::high_resolution_clock;

Timer::Timer() { Restart(); }

f64 Timer::Tick()
{
	auto t         = Clock::now();
	m_PreviousTick = m_LastTick;
	m_LastTick     = t.time_since_epoch().count();

	return DeltaTime();
}

void Timer::Restart()
{
	auto t      = Clock::now();
	m_StartTime = t.time_since_epoch().count();
	m_LastTick = m_PreviousTick = m_StartTime;
}

u64 Timer::DeltaTimeNanoseconds() const
{
	u64 dt = m_LastTick - m_PreviousTick;
	return dt;
}

u64 Timer::DeltaTimeMicroseconds() const { return DeltaTimeNanoseconds() / 1000; }

u64 Timer::DeltaTimeMilliseconds() const { return DeltaTimeMicroseconds() / 1000; }

f64 Timer::DeltaTime() const { return static_cast<f64>(DeltaTimeNanoseconds()) * 1e-9; }

f64 Timer::TimeSinceStart() const
{
	u64 t  = Clock::now().time_since_epoch().count();
	u64 dt = t - m_StartTime;
	return static_cast<f64>(dt) * 1e-9;
}

}