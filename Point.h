#pragma once

struct Point {
	Point()
	{
		this->x = 0;
		this->y = 0;
	}
	Point(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	float x, y;
};