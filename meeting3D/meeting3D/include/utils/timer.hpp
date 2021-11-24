#pragma once
#include<chrono>

/// <summary>
/// Class that allows the programmer to time a specific piece of code within a scope
/// </summary>
class Timer {
private:
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> end;
	std::chrono::duration<float> duration;
	float* timer;

public:
	explicit Timer(float* time) : timer(time){
		start = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> startDuration(0.0);
		duration = startDuration;
	}

	~Timer() {
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		*timer = duration.count();
	}
};