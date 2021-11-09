#pragma once

template<class T>
class Vector2d {

public:
	T x;
	T y;

	Vector2d() = default;
	Vector2d(T vx, T vy) : x(vx), y(vy) {}
};