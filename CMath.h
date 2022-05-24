#pragma once

#include <vector>
#include "Point.h"
#include "HitResult.h"

class CMath
{
public:
	static std::vector<std::vector<float>> Multiply(std::vector<std::vector<float>>& firstVector, std::vector<std::vector<float>>& secondVector);

	static void RotateAroundPoint(std::vector<std::vector<float>>& vectorToRotate, std::vector<float>& point, float angle);

	static bool bIsMatrix(std::vector<std::vector<float>>& vectorToCheck);

	static float DegreesToRadians(float degrees);

	static int RandBetween(int min, int max);

	/*
	 * Method to exclude safe to collision bounds point
	 * Other words excluding bounds that don't needed to be checked
	 */
	static std::vector<std::vector<float>> ExcludeSafeBounds(std::vector<std::vector<float>>& bounds, float xOutOfBounds, float yOutOfBounds);
	
	/*
	 * Insertion sort
	 */
	static void SortByX (std::vector<std::vector<float>>& bounds);

	/*
	 * Usingng Bresenham's line algorithm for tracing
	 */

	static HitResult TraceByColor(float x1f, float y1f, float x2f, float y2f, uint32_t color);
};

