#pragma once
#include <stdint.h>
#include <vector>
#include "Engine.h"

class Painter
{
public:
	/*
	 * Bresenham's line algorithm
	 */
	static void DrawLine(float x, float y, float x2, float y2, uint32_t color);

	static void DrawLineSequence(std::vector<std::vector<float>> sequence, uint32_t color, bool bIsCycled = true);

	static void PutPixel (int x, int y, uint32_t color);

	static uint32_t RGBToUInt32(int r, int g, int b);

private:

};

