#pragma once
#include<chrono>


class Timer {
private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
	float* timer;

public:
	Timer(float* time){
		start = std::chrono::high_resolution_clock::now();
		timer = time;
		duration = start - start;
	}

	~Timer() {
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		*timer = duration.count();
	}
};