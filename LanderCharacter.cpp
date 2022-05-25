
#include "LanderCharacter.h"
#include <vector>
#include <math.h>
#include <corecrt_math.h>
#include "Painter.h"
#include "CMath.h"
#include "HUD.h"
#include <algorithm>


LanderCharacter::LanderCharacter( float fuelRate, float burnModifier, float sideSize, float mass)
{	
	this->fuelRate = fuelRate;
	this->burnModifier = burnModifier;
	this->sideSize = sideSize;
	this->mass = mass;
}

void LanderCharacter::Spawn(float x, float y, float horizontalSpeed, float verticalSpeed, float fuel)
{
	bIsDead = false;
	bIsLanded = false;

	this->horizontalSpeed = horizontalSpeed;
	this->verticalSpeed = verticalSpeed;
	this->fuel = fuel;

	rotation = 90.f;

	bounds.clear();
	bounds.push_back({ x, y - sideSize, 1 });
	bounds.push_back({ x, y, 1 });
	bounds.push_back({ x + sideSize, y, 1});
	bounds.push_back({ x + sideSize, y - sideSize, 1});
	bounds.push_back({ x + sideSize / 2.f, y - sideSize * 1.5f, 1});
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

void LanderCharacter::Move(float dt)
{	
	AddPhysics(dt);
	for (int i = 0; i < bounds.size(); i++)
	{
		if(bIsDead) return;
		CheckCollision();
		if (bounds[i][0]< -xOutOfBounds || bounds[i][0] > SCREEN_WIDTH + xOutOfBounds || 
			bounds[i][1]< -yOutOfBounds || bounds[i][1] > SCREEN_HEIGHT)
		{
			bIsDead = true;
			return;
		}
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
	CMath::RotateAroundPoint(bounds, massCenter, value * dt);
	printf("Rotation is %f", rotation);
}

void LanderCharacter::AddPhysics(float dt)
{
	verticalSpeed -= g * mass * dt;
	horizontalSpeed -= atmosResistModifier * horizontalSpeed * dt;
}

void LanderCharacter::CalculateMassCenter()
{
	massCenter[0] = abs(bounds[0][0] + bounds[2][0]) / 2.f;
	massCenter[1] = abs(bounds[2][1] + bounds[0][1]) / 2.f;
}

void LanderCharacter::CheckCollision()
{
	optimizedBounds = CMath::ExcludeSafeBounds(bounds, xOutOfBounds, yOutOfBounds);

	for (int i = 1; i<optimizedBounds.size(); i++)
	{	
		SetCollisionOffset(optimizedBounds, 1.f);
		//if(optimizedBounds[i - 1][0] < massCenter[0])
		HitResult hit  = CMath::TraceByColor(
			optimizedBounds[i - 1][0],
			optimizedBounds[i - 1][1],
			optimizedBounds[i][0],
			optimizedBounds[i][1],
			Painter::RGBToUInt32(0, 0, 0)
		);

		if(hit.bHit)
		{
			if(hit.hitObject == LANDSCAPE_COLOR)
			{
    				bIsDead = true;
				return;
			}
			if (hit.hitObject == PAD_COLOR && GetVelocity()<killVelocity)
			{
				verticalSpeed = -verticalSpeed*elasticity;
				horizontalSpeed *= friction;

				if(GetVelocity()<1.f)
				{
					bIsLanded = true;
				}
				return;
			}
			if (hit.hitObject == PAD_COLOR && GetVelocity() > killVelocity)
			{
				bIsDead = true;
				return;
			}
			if (hit.hitObject == LANDER_COLOR) return;	
		}
	}
}

void LanderCharacter::SetCollisionOffset(std::vector<std::vector<float>>& optimizedBounds, float offset)
{
	CalculateMassCenter();
	
	for(int i = 0; i< optimizedBounds.size(); i++)
	{
		optimizedBounds[i][0] = optimizedBounds[i][0] >massCenter[0] ? optimizedBounds[i][0] + offset : optimizedBounds[i][0] - offset;
		optimizedBounds[i][1] = optimizedBounds[i][1] > massCenter[1] ? optimizedBounds[i][1] + offset : optimizedBounds[i][1] - offset;
	}
}

float LanderCharacter::GetVelocity()
{
	return abs(horizontalSpeed) + abs(verticalSpeed);
}

void LanderCharacter::Draw()
{
	if (!buffer && bounds.empty()) return;

	//Drawing Lander
	Painter::DrawLineSequence(bounds, LANDER_COLOR);

	//SetCollisionOffset(optimizedBounds, 2.f);
	//Painter::DrawLineSequence(optimizedBounds, Painter::RGBToUInt32(0, 255, 0), false);
	/*CalculateMassCenter();*/
	uint32_t horizontal = (uint32_t)roundf(massCenter[0]);
	uint32_t vertical = (uint32_t)roundf(massCenter[1]);
	Painter::PutPixel(horizontal, vertical, LANDER_COLOR);
}

