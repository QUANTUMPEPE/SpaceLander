#pragma once

#include "Point.h"
#include <vector>
#include "Engine.h"

#define _USE_MATH_DEFINES

class LanderCharacter
{
public:
	LanderCharacter(
		float horizontalSpeed = 0.f,
		float verticalSpeed = 0.f,
		float rotation = 90.f,
		float fuel = 10000.f,
		float fuelRate = 100.f,
		float burnModifier = 50.f,
		float sideSize = 15.f,
		float mass = 20.f
	);

	void Spawn(float horizontal, float vertical);
	void BurnEngine(float dt);
	void Move(float dt);
	void Rotate(float value, float dt);
	void Draw();

	~LanderCharacter()
	{
	}
private:
	float horizontalSpeed = 0.f;
	float verticalSpeed = 0.f;
	float fuel = 100.f;
	float rotation = 0.f;
	float burnModifier = 100000.f;
	float fuelRate = 100.f;
	float mass = 1.f;
	float elasticity = 0.95f;
	float friction = 0.95f;

	float g = 1.62f;
	float atmosResistModifier = 0.01f;

	//Size of bounds box
	float sideSize = 10.f;
	
	bool bIsDead = false;
	float xOutOfBounds = 100.f;
	float yOutOfBounds = 300.f;
	const float killVelocity = 50.f;

	std::vector<std::vector<float>> optimizedBounds;

	/*
	 *	In bounds [Point num][0 = horizontal axis; 1 = vertical axis; 2 = for matrix multiplying] 
	 */

	std::vector<std::vector<float>> bounds;
	std::vector<float> massCenter {3, 1};

	void SpendFuel(float value, float dt);
	void AddPhysics(float dt);
	void CalculateMassCenter();
	
	/**
	 * Checking collision by taking bottom sides of lander 
	 *  and comparing y+1 side coord to land color in buffer
	 */
	void CheckCollision();
	void SetCollisionOffset(std::vector<std::vector<float>>& optimizedBounds, float offset);
	
public:
	std::vector<std::vector<float>> GetBounds() { return bounds; }
	void SetG (float value) { g = value; }
	void SetAtmosphericResistance (float value) { atmosResistModifier = value; }
	float GetRotation(){ return rotation; }
	float GetSize(){ return sideSize; }
	bool IsDead(){ return bIsDead; }

	float GetFuel() {return fuel; }
	float GetVerticalSpeed() {return abs(verticalSpeed); }
	float GetHorizontalSpeed() {return abs(horizontalSpeed); }
	float GetVelocity();
};

