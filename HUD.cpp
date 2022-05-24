#include "HUD.h"
#include <WinUser.h>
#include <wingdi.h>
#include <WinBase.h>


HUD::HUD(LanderCharacter* character)
{
	if(character)
	{
		this->character = character;
	}

	gameWindow = GetForegroundWindow();
		
	if(gameWindow)
	{	
		dc = GetDC(gameWindow);
		font = CreateFont(-16, 0, 0, 0, 0, 0U, 0U, 0U, ANSI_CHARSET,0U, 0U, 0U, 0U, TEXT("Arial"));
		old = SelectObject(dc, font);

		SetBkMode(dc, TRANSPARENT);
		SetTextColor(dc, 0x00FFFFFF);  
	}
}

void HUD::Update()
{
	GetClientRect(gameWindow, &rc);
	if(character)
	{
		std::string temp = sTime + std::to_string(time);
		DrawText(dc, temp.c_str(), lstrlen(temp.c_str()), &rc, DT_LEFT);

		temp = sFuel + std::to_string(character->GetFuel());
		DrawText(dc, temp.c_str(), lstrlen(temp.c_str()), &rc, DT_RIGHT);

		rc.top+= 20;

		temp = sScore + std::to_string(score);
		DrawText(dc, temp.c_str(), lstrlen(temp.c_str()), &rc, DT_LEFT);

		temp = sHorSpeed + std::to_string(character->GetHorizontalSpeed());
		DrawText(dc, temp.c_str(), lstrlen(temp.c_str()), &rc, DT_RIGHT);

		rc.top += 20;

		temp = sVertSpeed + std::to_string(character->GetVerticalSpeed());
		DrawText(dc, temp.c_str(), lstrlen(temp.c_str()), &rc, DT_RIGHT);
	}
}

void HUD::AddToTime(float dt)
{
	time += dt;
}

void HUD::AddToScore(int value)
{
	score += value;
}
