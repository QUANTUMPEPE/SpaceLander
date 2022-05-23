
#include "LanderCharacter.h"
#include <vector>
#include <math.h>
#include <corecrt_math.h>
#include "VectorTransforms.h"
#include "Painter.h"


LanderCharacter::LanderCharacter(float horizontalSpeed, float verticalSpeed, float rotation, float fuel, float fuelRate, float burnModifier, float sideSize, float mass)
{
	this->horizontalSpeed = horizontalSpeed;
	this->verticalSpeed = verticalSpeed;
	this->rotation = rotation;
	this->fuel = fuel;
	this->fuelRate = fuelRate;
	this->burnModifier = burnModifier;
	this->sideSize = sideSize;
	this->mass = mass;
}

void LanderCharacter::spawn(float horizontal, float vertical)
{
	bounds.clear();
	bounds.push_back({ horizontal, vertical, 1 });
	bounds.push_back({horizontal + sideSize, vertical, 1});
	bounds.push_back({horizontal + sideSize, vertical - sideSize, 1});
	bounds.push_back({horizontal + sideSize / 2.f, vertical - sideSize * 1.5f, 1});
	bounds.push_back({horizontal, vertical - sideSize, 1});
}

void LanderCharacter::burnEngine(float dt)
{
	if(fuel < 0.f) return;
	spendFuel(fuelRate, dt);

	verticalSpeed += burnModifier * sin(rotation * M_PI / 180.f) * dt;
	horizontalSpeed += burnModifier * cos(rotation * M_PI / 180.f) * dt;
}

void LanderCharacter::spendFuel(float value, float dt)
{
	if (fuel - value * dt < 0)
	{
		fuel = 0;
		return;
	}
	fuel -= value * dt;
}

void LanderCharacter::addPhysics(float dt)
{
	verticalSpeed -= g*mass*dt;
	horizontalSpeed -= atmosResistModifier*horizontalSpeed*dt;
}

void LanderCharacter::calculateMassCenter()
{
	float horizontal = abs(bounds[0][0] + bounds[1][0]) /2.f;
	float vertical = abs(bounds[2][1] + bounds[0][1]) / 2.f;
	massCenter[0] = horizontal;
	massCenter[1] = vertical;
}

void LanderCharacter::move(float dt)
{	
	addPhysics(dt);
	for (int i = 0; i < bounds.size(); i++)
	{
		bounds[i][0] += horizontalSpeed * dt;
		bounds[i][1] += -verticalSpeed * dt;
	}
}

void LanderCharacter::rotate(float value, float dt)
{	
	if((rotation + value) >= 360.f)
	{
		rotation = abs((rotation - value * dt) - 360.f);
	}

	else if ((rotation + value) < 0.f)
	{
		rotation = abs(360.f + (rotation - value * dt));
	}
	else
	{
		rotation -= value * dt;
	}
	calculateMassCenter();
	VectorTransforms::RotateAroundPoint(bounds,	massCenter, value * dt);
	printf("Rotation is %f", rotation);
}

void LanderCharacter::draw()
{
	if (!buffer && bounds.empty()) return;

	/*for (int i = 0; i < bounds.size(); i++)
	{
		uint32_t horizontal = (uint32_t)roundf(bounds[i][0]);
		uint32_t vertical = (uint32_t)roundf(bounds[i][1]);
		if(horizontal < 0 || horizontal > SCREEN_WIDTH || vertical < 0 || vertical > SCREEN_HEIGHT) continue;
		buffer[vertical][horizontal] = 1000;
	}*/

	Painter::DrawLine(bounds[0][0], bounds[0][1], bounds[1][0], bounds[1][1], 1000);
	Painter::DrawLineSequence(bounds, 1000);

	calculateMassCenter();
	uint32_t horizontal = (uint32_t)roundf(massCenter[0]);
	uint32_t vertical = (uint32_t)roundf(massCenter[1]);
	buffer[vertical][horizontal] = 1000;

	
}

