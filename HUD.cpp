#include "HUD.h"
#include <WinUser.h>
#include <wingdi.h>
#include <WinBase.h>
#include <iostream>
#include <fstream>


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
		fontMenu = CreateFont(-32, 0, 0, 0, 0, 0U, 0U, 0U, ANSI_CHARSET,0U, 0U, 0U, 0U, TEXT("Arial"));
		old = SelectObject(dc, font);

		SetBkMode(dc, TRANSPARENT);
		SetTextColor(dc, 0x00FFFFFF);  

		ReadHighscore();
	}
}

void HUD::Update()
{
	std::string temp;
	GetClientRect(gameWindow, &rc);
	if(character && bGameRunning)
	{
		temp = sTime + std::to_string(time);
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

	if(!bGameRunning)
	{
		rc.top += 200;
		DrawText(dc, sTitle.c_str(), lstrlen(sTitle.c_str()), &rc, DT_CENTER);

		rc.top += 36;
		temp = sHighscore + std::to_string(highscore);
		DrawText(dc, temp.c_str(), lstrlen(temp.c_str()), &rc, DT_CENTER);

		rc.top += 36;
		temp = sScore + std::to_string(lastScore);
		DrawText(dc, temp.c_str(), lstrlen(temp.c_str()), &rc, DT_CENTER);

		rc.top += 36;
		DrawText(dc, sControls.c_str(), lstrlen(sControls.c_str()), &rc, DT_CENTER);
	}
}

void HUD::AddToTime(float dt)
{
	time += dt;
}

void HUD::CountScore()
{
	score += (character->GetFuel()* (1.f + (time/60.f)));
}

void HUD::Reset()
{
	time = 0.f;
	lastScore = score;
	if(highscore<score)
	{
		highscore = score;
		WriteHighscore();
	}
	score = 0.f;
}

void HUD::ResetTime()
{
	time = 0.f;
}

void HUD::WriteHighscore()
{
	std::ofstream highscoreFile;
	highscoreFile.open("highscore.txt");
	highscoreFile << highscore;
	highscoreFile.close();
}

void HUD::ReadHighscore()
{
	std::string line;
	std::ifstream infile("highscore.txt");
	if(infile)
	{
		std::getline(infile, line);
		highscore = std::stoi(line);
	}
	else
	{
		std::ofstream{ "highscore.txt" };
	}

}
