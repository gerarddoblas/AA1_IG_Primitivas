#pragma once

#include <cmath>
#include <GLFW/glfw3.h>

#define TIME TimeManager::Instance()

class TimeManager
{
private:
	TimeManager()
	{
		_deltaTime = 0.0f;
		_elapsedTime = glfwGetTime();
		_previousElapsedTime = 0.0f;

		_frameTime = 1.0f / (float)_FPS;
	}
	~TimeManager() = default;

	TimeManager(const TimeManager& t) = delete;
	TimeManager& operator = (const TimeManager& t) = delete;

	//Time control
	float _deltaTime;
	float _elapsedTime;
	float _previousElapsedTime;

	//FPS control
	const int _FPS = 60;
	float _frameTime;


public:
	static TimeManager& Instance()
	{
		static TimeManager instance;

		return instance;
	}

	float GetDeltaTime() { return _deltaTime; }
	float GetElapsedTime() { return _elapsedTime; }
	float GetFrameTime() { return _frameTime; }

	bool ShouldUpdateGame() { return _deltaTime >= _frameTime; }

	void ResetDeltaTime()
	{
		//_deltaTime -= (float)floor(_deltaTime / _frameTime) * _frameTime;
	}

	void Update()
	{
		_elapsedTime = (float)glfwGetTime();
		_deltaTime = _elapsedTime - _previousElapsedTime;
		_previousElapsedTime = _elapsedTime;
	}
};