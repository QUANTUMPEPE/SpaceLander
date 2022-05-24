#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include <iostream>
#include "LanderCharacter.h"
#include "Level.h"
#include "HUD.h"

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()

LanderCharacter* character;
Level* level;
HUD* hud;
// initialize game data in this function
void initialize()
{
    srand(time(0));
    character = new LanderCharacter();
    character->Spawn(500.f, 350.f);

    level = new Level(character->GetSize());
    level->Generate(15.f, 450, SCREEN_HEIGHT - 5, 35, 0.5f);
    
    if(character)
    {
        hud = new HUD(character);
    }

}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
  if(!is_window_active()) return;

  if (is_key_pressed(VK_ESCAPE))
    schedule_quit_game();
    
  if(character && !character->IsDead())
  {
    cout<< character->GetRotation() <<endl;
    if(is_key_pressed(VK_SPACE))
    {
        character->BurnEngine(dt);
    }
    if(is_key_pressed(VK_LEFT) && !is_key_pressed(VK_RIGHT))
    {
        character->Rotate(-90.f, dt);
    }
	if (is_key_pressed(VK_RIGHT) && !is_key_pressed(VK_LEFT))
	{
		character->Rotate(90.f, dt);
	}
    character->Move(dt);
  }
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
  // clear backbuffer
  memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
  if(character && !character->IsDead())
  {
    character->Draw();
  }
  if(level)
  {
    level->Draw();
  }
}

// free game data in this function
void finalize()
{
    delete character;
    delete level;
}

