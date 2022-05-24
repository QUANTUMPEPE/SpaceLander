#pragma once
#include "Point.h"
#include <stdint.h>

struct HitResult
{
	bool bHit;
	Point hitPoint;
	uint32_t hitObject;
};