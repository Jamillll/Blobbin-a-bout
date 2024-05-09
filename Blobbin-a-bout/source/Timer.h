#pragma once

class Timer
{
private:
	double* m_ScopeTime = nullptr;
	double m_StartTime;

public:
	Timer(double* scopeTime);

	double GetTime();

	~Timer();
};