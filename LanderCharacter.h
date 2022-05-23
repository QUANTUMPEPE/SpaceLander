#pragma once

#include "Point.h"
#include <vector>


#define _USE_MATH_DEFINES

class LanderCharacter
{
public:
	LanderCharacter(
		float horizontalSpeed = 0.f,
		float verticalSpeed = 0.f,
		float rotation = 0.f,
		float fuel = 100.f,
		float fuelRate = 1.f,
		float burnModifier = 10.f,
		float sideSize = 10.f
	);

	void spawn(float location);
	void burnEngine();
	void move();
	void rotate(float value);

private:
	float horizontalSpeed = 0.f;
	float verticalSpeed = 0.f;
	float fuel = 100.f;
	float rotation = 0.f;
	float burnModifier = 10.f;
	float fuelRate = 1.f;

	//Size of bounds box
	float sideSize = 10.f;

	Point *bounds;

	void spendFuel(float value);

	~LanderCharacter()
	{
		delete bounds;
	}

public:
	Point* GetBounds() { return bounds; }
};

