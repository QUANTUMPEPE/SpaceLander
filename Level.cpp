#include "Level.h"
#include <stdlib.h>
#include <time.h>
#include "Painter.h"
#include "CMath.h"
#include <algorithm>

Level::Level()
{

}

void Level::Generate(float radius, int minHeight, int maxHeight)
{
	
	float y = CMath::RandBetween(minHeight, maxHeight);
	float x = 0;

	landBounds.push_back({x,y});

	while (x < SCREEN_WIDTH)
	{
		float nextX = landBounds.back()[0] + radius * cos(CMath::DegreesToRadians(CMath::RandBetween(-90, 90)));
		float nextY = landBounds.back()[1] + radius * sin(CMath::DegreesToRadians(CMath::RandBetween(-90, 90)));

		nextY = clamp((int)roundf(nextY), minHeight, maxHeight);

		landBounds.push_back({nextX, nextY});
		x = nextX;
	}
	Draw();
}

void Level::Draw()
{
	Painter::DrawLineSequence(landBounds, 1000, false);
}
