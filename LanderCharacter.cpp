
#include "LanderCharacter.h"
#include <vector>
#include <math.h>


LanderCharacter::LanderCharacter(float horizontalSpeed, float verticalSpeed, float rotation, float fuel, float fuelRate, float burnModifier, float sideSize)
{
	this->horizontalSpeed = horizontalSpeed;
	this->verticalSpeed = verticalSpeed;
	this->rotation = rotation;
	this->fuel = fuel;
	this->fuelRate = fuelRate;
	this->burnModifier = burnModifier;
	this->sideSize = sideSize;
}

void LanderCharacter::spawn(float location)
{
	//if(bounds) delete bounds;
	bounds = new Point [4] { Point(location, location),  Point(location + sideSize, location),  Point(location , location + sideSize),  Point(location + sideSize, location + sideSize) };
}

void LanderCharacter::burnEngine()
{
	if(fuel < 0.f) return;
	spendFuel(fuelRate);

	verticalSpeed += burnModifier * sin(rotation * M_PI / 180);
	horizontalSpeed += burnModifier * cos(rotation * M_PI / 180);
}

void LanderCharacter::spendFuel(float value)
{
	if (fuel - value < 0)
	{
		fuel = 0;
		return;
	}
	fuel -= value;
}

void LanderCharacter::move()
{
	if(!bounds) return;
	for (int i = 0; i < sizeof(bounds); i++)
	{
		bounds[i].x += horizontalSpeed;
		bounds[i].y += verticalSpeed;
	}
}

void LanderCharacter::rotate(float value)
{	
	if((rotation + value) > 360.f)
	{
		rotation = abs(360.f - (rotation + value));
		return;
	}

	if ((rotation + value) < 0.f)
	{
		rotation = abs(360.f + (rotation + value));
		return;
	}

	rotation += value;
}
