#pragma once
#include "LanderCharacter.h"
#include <stdio.h>
#include <windows.h>


class HUD
{
public:
	HUD(LanderCharacter* character);
	TCHAR* str = (TCHAR*)("Hello DrawText !!!");
	void Update();
private:
	LanderCharacter* character;
	HWND gameWindow;
	HDC dc;
	RECT rc;
	HFONT font;
	HGDIOBJ old;
};

