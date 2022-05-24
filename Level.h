#pragma once
#include "Engine.h"
#include <vector>

using namespace std;

class Level
{
public:
	Level ();

	void Generate(float radius, int minHeight, int maxHeight);

	void Draw();
private:
	//float radius = 30.f;
	//int minHeight = 450;
	//int maxHeight = SCREEN_HEIGHT-5;
	vector<vector<float>> landBounds;
};

