#pragma once
#include "LanderCharacter.h"
#include <stdio.h>
#include <windows.h>
#include <string>
#include "Painter.h"

#define LANDSCAPE_COLOR Painter::RGBToUInt32(200, 200, 200)
#define PAD_COLOR Painter::RGBToUInt32(0, 255, 0)
#define LANDER_COLOR Painter::RGBToUInt32(255, 0, 0)

class HUD
{
public:
	HUD(LanderCharacter* character);
	void Update();

	void AddToTime(float dt);
	void AddToScore(int value);
private:
	LanderCharacter* character;
	HWND gameWindow;
	HDC dc;
	RECT rc;
	HFONT font;
	HGDIOBJ old;

	std::string sHorSpeed = ("Horizontal Speed: ");
	std::string sVertSpeed = ("Vertical Speed: ");
	std::string sFuel = ("Fuel: ");

	std::string sTime = ("Time: ");
	std::string sScore = ("Score: ");

	float time = 0.f;
	int score = 0;
};
 
