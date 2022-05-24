#pragma once
#include "Engine.h"
#include <vector>


class Level
{
public:
	Level (float characterSizeSize);

	void Generate(float radius, int minHeight, int maxHeight, int padFreq, float dificulty);

	void Draw();
private:
	float characterSize;

	/*
	 *	In level [Point num][0 = horizontal axis; 1 = vertical axis]
	 */
	std::vector<std::vector<float>> landBounds;
	std::vector<bool> landType;
};

