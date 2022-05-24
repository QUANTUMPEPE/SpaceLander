
#include "LanderCharacter.h"
#include <vector>
#include <math.h>
#include <corecrt_math.h>
#include "Painter.h"
#include "CMath.h"


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

void LanderCharacter::Spawn(float horizontal, float vertical)
{
	bounds.clear();
	bounds.push_back({ horizontal, vertical, 1 });
	bounds.push_back({horizontal + sideSize, vertical, 1});
	bounds.push_back({horizontal + sideSize, vertical - sideSize, 1});
	bounds.push_back({horizontal + sideSize / 2.f, vertical - sideSize * 1.5f, 1});
	bounds.push_back({horizontal, vertical - sideSize, 1});
}

void LanderCharacter::BurnEngine(float dt)
{
	if(fuel < 0.f) return;
	SpendFuel(fuelRate, dt);

	verticalSpeed += burnModifier * sin(CMath::DegreesToRadians(rotation)) * dt;
	horizontalSpeed += burnModifier * cos(CMath::DegreesToRadians(rotation)) * dt;
}

void LanderCharacter::SpendFuel(float value, float dt)
{
	if (fuel - value * dt < 0)
	{
		fuel = 0;
		return;
	}
	fuel -= value * dt;
}

void LanderCharacter::AddPhysics(float dt)
{
	verticalSpeed -= g*mass*dt;
	horizontalSpeed -= atmosResistModifier*horizontalSpeed*dt;
}

void LanderCharacter::CalculateMassCenter()
{
	float horizontal = abs(bounds[0][0] + bounds[1][0]) /2.f;
	float vertical = abs(bounds[2][1] + bounds[0][1]) / 2.f;
	massCenter[0] = horizontal;
	massCenter[1] = vertical;
}

void LanderCharacter::Move(float dt)
{	
	AddPhysics(dt);
	for (int i = 0; i < bounds.size(); i++)
	{
		bounds[i][0] += horizontalSpeed * dt;
		bounds[i][1] += -verticalSpeed * dt;
	}
}

void LanderCharacter::Rotate(float value, float dt)
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
	CalculateMassCenter();
	CMath::RotateAroundPoint(bounds,	massCenter, value * dt);
	printf("Rotation is %f", rotation);
}

void LanderCharacter::Draw()
{
	if (!buffer && bounds.empty()) return;

	//Drawing Lander
	Painter::DrawLineSequence(bounds, 1000);

	CalculateMassCenter();
	uint32_t horizontal = (uint32_t)roundf(massCenter[0]);
	uint32_t vertical = (uint32_t)roundf(massCenter[1]);
	Painter::PutPixel(horizontal, vertical, 1000);
}

