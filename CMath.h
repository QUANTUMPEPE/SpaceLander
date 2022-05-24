#pragma once

#include <vector>

using namespace std;

class CMath
{
public:
	static vector<vector<float>> Multiply(vector<vector<float>>& firstVector, vector<vector<float>>& secondVector);

	static void RotateAroundPoint(vector<vector<float>>& vectorToRotate, vector<float>& point, float angle);

	static bool bIsMatrix(vector<vector<float>>& vectorToCheck);

	static float DegreesToRadians(float degrees);

	static int RandBetween(int min, int max);
};

