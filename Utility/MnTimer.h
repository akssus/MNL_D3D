#pragma once
#include <chrono>

namespace MNL
{
	class MnTimer;
	/*
	time value is duration in milliseconds
	*/
	class MnTime
	{
	public:
		MnTime();
		~MnTime();
		/*
		The time that passed in game world. It could be slower or faster
		*/
		double ScaledTime() const;
		/*
		The time that really passed in real world
		*/
		double GenuineTime() const;

	private:
		friend class MnTimer;

	private:
		double m_time;
		double m_timeScale;
	};

	class MnTimer
	{
	public:
		MnTimer();
		~MnTimer();

		void SetTimeScale(float timeScale);

		void Start();
		void Pause();
		bool IsPlaying() const;

		MnTime GetElapsedTime();

	private:
		bool m_isPlaying;
		float m_timeScale;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTick;

	};
}
