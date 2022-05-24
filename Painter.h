#pragma once
#include <stdint.h>
#include <vector>
#include "Engine.h"

using namespace std;

class Painter
{
public:
	static void DrawLine(float x, float y, float x2, float y2, int color);

	static void DrawLineSequence(vector<vector<float>> sequence, int color, bool bIsCycled = true);

	static void PutPixel (int x, int y, int color);

private:

};

