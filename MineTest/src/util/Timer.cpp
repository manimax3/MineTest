#include "Timer.h"

using namespace std::chrono;

typedef std::chrono::duration<float, std::milli> milliseconds_type;
typedef std::chrono::duration<double, std::milli> milliseconds_type_double;

Timer::Timer()
{
	reset();
}

void Timer::reset()
{
	m_Start = HighResClock::now();
}

float Timer::elapsed()
{
	return duration_cast<milliseconds_type>(HighResClock::now() - m_Start).count() / 1000.f;
}

double Timer::elapsedD()
{
	return duration_cast<milliseconds_type_double>(HighResClock::now() - m_Start).count() / 1000.f;
}

float Timer::restart()
{
	float tmp = duration_cast<milliseconds_type>(HighResClock::now() - m_Start).count() / 1000.f;
	reset();
	return tmp;
}