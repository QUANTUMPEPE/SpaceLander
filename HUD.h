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

	void CountScore();
	void Reset();
	void ResetTime();
	void WriteHighscore();
	void ReadHighscore();

private:
	LanderCharacter* character;
	HWND gameWindow;
	HDC dc;
	RECT rc;
	HFONT font;
	HFONT fontMenu;
	HGDIOBJ old;

	std::string sHorSpeed = ("Horizontal Speed: ");
	std::string sVertSpeed = ("Vertical Speed: ");
	std::string sFuel = ("Fuel: ");

	std::string sTime = ("Time: ");
	std::string sScore = ("Score: ");
	std::string sHighscore = ("High score: ");

	std::string sTitle = ("Space Lander  Press ENTER to start!");

	float time = 0.f;
	int score = 0;
	int lastScore = 0;
	int highscore = 0;

	bool bGameRunning = false;

public:
	bool IsGameRunnig() { return bGameRunning; }
	void SetGameState(bool state) { bGameRunning = state; }
};
 
