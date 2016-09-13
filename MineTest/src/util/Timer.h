#pragma once
#include <chrono>

typedef std::chrono::high_resolution_clock HighResClock;

class Timer
{
public:
	Timer();
	~Timer() = default;

	//Just resets the timer without returning its value
	void reset();
	//Returns value in seconds!
	float elapsed();
	double elapsedD();
	//Returns elapsed time and resets!
	float restart();
private:
	std::chrono::time_point<HighResClock> m_Start;
};