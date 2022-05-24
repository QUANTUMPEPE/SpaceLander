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
		font = CreateFont(-24, 0, 0, 0, 0, ANSI_CHARSET, 0U, 0U, 0U, 0U, 0U, 0U, 0U, TEXT("Arial"));
		old = SelectObject(dc, font);

		GetClientRect(gameWindow, &rc);
		rc.bottom /= 14L;
		SetBkMode(dc, TRANSPARENT);
		SetTextColor(dc, 0x0000FF00);  // цвет текста(зелённый)

		DrawText(dc, str, lstrlen(str), &rc, DT_CENTER);
	}

}

void HUD::Update()
{

}
