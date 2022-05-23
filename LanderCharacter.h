#pragma once

#include "Point.h"
#include <vector>
#include "Engine.h"


#define _USE_MATH_DEFINES

using namespace std;

class LanderCharacter
{
public:
	LanderCharacter(
		float horizontalSpeed = 0.f,
		float verticalSpeed = 0.f,
		float rotation = 90.f,
		float fuel = 10000.f,
		float fuelRate = 1.f,
		float burnModifier = 50.f,
		float sideSize = 10.f,
		float mass = 10.f
	);

	void spawn(float horizontal, float vertical);
	void burnEngine(float dt);
	void move(float dt);
	void rotate(float value, float dt);
	void draw(uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH]);

	~LanderCharacter()
	{
	}
private:
	float horizontalSpeed = 0.f;
	float verticalSpeed = 0.f;
	float fuel = 100.f;
	float rotation = 0.f;
	float burnModifier = 100000.f;
	float fuelRate = 1.f;
	float mass = 1.f;

	float g = 1.62f;
	float atmosResistModifier = 0.01f;

	//Size of bounds box
	float sideSize = 10.f;

	/*
	 *	In bounds [Point num][0 = horizontal axis; 1 = vertical axis; 2 = for matrix multiplying] 
	 */

	vector<vector<float>> bounds;
	vector<float> massCenter {3, 1};

	void spendFuel(float value, float dt);
	void addPhysics(float dt);
	void calculateMassCenter();
	
public:
	vector<vector<float>> GetBounds() { return bounds; }
	void SetG (float value) { g = value; }
	void SetAtmosphericResistance (float value) { atmosResistModifier = value; }
	float GetRotation(){ return rotation; }
};

