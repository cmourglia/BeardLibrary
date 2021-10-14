#pragma once

#include <Beard/Macros.h>

namespace Beard
{
class Timer
{
public:
	Timer();

	// Get the time since the last call to Tick() or since the start if called
	// for the first time
	f64 Tick();

	// Set the start time to the current time
	void Restart();

	// Get the time elapsed between the two last calls to Tick()
	f64 DeltaTime() const;
	u64 DeltaTimeNanoseconds() const;
	u64 DeltaTimeMicroseconds() const;
	u64 DeltaTimeMilliseconds() const;

	// Get the time since the timer started (or since the last call to
	// Restart()). Who could have guessed ?
	f64 TimeSinceStart() const;

private:
	u64 m_StartTime    = 0;
	u64 m_LastTick     = 0;
	u64 m_PreviousTick = 0;
};
}