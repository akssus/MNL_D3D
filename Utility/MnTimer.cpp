#include "MnTimer.h"

using namespace MNL;


MnTime::MnTime():m_time(0.0),m_timeScale(1.0)
{

}
MnTime::~MnTime()
{

}
/*
The time that passed in game world. It could be slower or faster
*/
double MnTime::ScaledTime() const
{
	return m_time;
}

double MnTime::GenuineTime() const
{
	return m_time * m_timeScale;
}


/***************************************************************************************************/


MnTimer::MnTimer():m_isPlaying(false),
m_timeScale(1.0f),
m_lastTick(std::chrono::high_resolution_clock::now())
{

}

MnTimer::~MnTimer()
{

}
void MnTimer::SetTimeScale(float timeScale)
{
	m_timeScale = timeScale;
}
void MnTimer::Start()
{
	m_isPlaying = true;
	m_lastTick = std::chrono::high_resolution_clock::now();
}
void MnTimer::Pause()
{
	m_isPlaying = false;
}

bool MnTimer::IsPlaying() const
{
	return m_isPlaying;
}

MnTime MnTimer::GetElapsedTime()
{
	MnTime elapsedTime;
	if (m_isPlaying)
	{
		auto currentTick = std::chrono::high_resolution_clock::now();
		auto timeDelta = std::chrono::duration_cast<std::chrono::milliseconds>(currentTick - m_lastTick);
		m_lastTick = currentTick;
		elapsedTime.m_time = timeDelta.count();
		elapsedTime.m_timeScale = m_timeScale;
	}
	return elapsedTime;
}