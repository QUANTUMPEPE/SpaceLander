#include "Level.h"
#include <stdlib.h>
#include <time.h>
#include "Painter.h"
#include "CMath.h"
#include <algorithm>
#include "HUD.h"

Level::Level(float characterSizeSize)
{
	this->characterSize = characterSizeSize;
}

void Level::Generate(float radius, int minHeight, int maxHeight, int padFreq, float difficulty)
{
	difficulty = std::clamp(difficulty, 0.f, 1.f);
	float y = CMath::RandBetween(minHeight, maxHeight);
	float x = 0;

	landBounds.push_back({x,y});

	float nextX = 0;
	float nextY = 0;

	while (x < SCREEN_WIDTH)
	{
		if((int)roundf(x) % padFreq == 0)
		{
			if(landType.empty()) {landType.push_back(true);}
			else {landType.back() = true;}
				
			nextY = landBounds.back()[1];
			nextX = landBounds.back()[0] + characterSize + characterSize*(1.f - difficulty);
			
			landType.push_back(true);
		}
		else
		{
			nextX = landBounds.back()[0] + radius * cos(CMath::DegreesToRadians(CMath::RandBetween(-90, 90)));
			nextY = landBounds.back()[1] + radius * sin(CMath::DegreesToRadians(CMath::RandBetween(-90, 90)));
			nextY = std::clamp((int)roundf(nextY), minHeight, maxHeight);
			landType.push_back(false);
		}
		landBounds.push_back({nextX, nextY});

		x = nextX;
	}
	Draw();
}

void Level::Draw()
{
	if(landBounds.size() != landType.size()) return;
	for(int i = 1; i< landBounds.size(); i++)
	{
		if (landType[i-1] == true && landType[i] == true)
		{
			Painter::DrawLine(landBounds[i-1][0], landBounds[i - 1][1], landBounds[i][0], landBounds[i][1], PAD_COLOR);
			continue;
		}
		Painter::DrawLine(landBounds[i - 1][0], landBounds[i - 1][1], landBounds[i][0], landBounds[i][1], LANDSCAPE_COLOR);
	}
}
