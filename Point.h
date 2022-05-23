#pragma once

struct Point {
	Point()
	{
		this->horizontal = 0;
		this->vertical = 0;
	}
	Point(float horizontal, float vertical)
	{
		this->horizontal = horizontal;
		this->vertical = vertical;
	}
	float horizontal, vertical;
};