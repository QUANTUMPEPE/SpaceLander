#pragma once
#include <stdint.h>
#include "Engine.h"

class Painter
{
public:
	Painter(uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH]);

private:
	uint32_t *buffer;
};

