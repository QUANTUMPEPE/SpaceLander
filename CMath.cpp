#include "CMath.h"

#include <vector>
#include <iostream>
#include <corecrt_math_defines.h>

vector<vector<float>> CMath::Multiply(vector<vector<float>>& firstVector, vector<vector<float>>& secondVector)
{
	if (!bIsMatrix(firstVector) || !bIsMatrix(secondVector)) throw std::invalid_argument("One of vectors is not a matrix");
	int firstRows = (int)firstVector.size();
	int firstCols = (int)firstVector[0].size();
	int secondRows = (int)secondVector.size();
	int secondCols = (int)secondVector[0].size();

	if (firstCols != secondRows) throw std::invalid_argument("Cols of first vector doest match rows of second");
	vector<vector<float>> product(firstRows, vector<float>(secondCols));

	for (int i = 0; i < firstRows; i++)
	{
		for (int j = 0; j < secondCols; j++)
		{
			product[i][j] = 0;
			for (int k = 0; k < firstCols; k++)
			{
				product[i][j] += firstVector[i][k] * secondVector[k][j];
			}
		}
	}
	return product;
}

void CMath::RotateAroundPoint(vector<vector<float>>& vectorToRotate, vector<float>& point, float angle)
{
	vector<vector<float>> transformToPoint{
		{1, 0, 0},
		{0, 1, 0},
		{-point[0], -point[1], 1}
	};

	vector<vector<float>> transformFromPoint{
		{1, 0, 0},
		{0, 1, 0},
		{point[0], point[1], 1}
	};

	vector<vector<float>> transformAngle{
		{cos(DegreesToRadians(angle)), sin(DegreesToRadians(angle)), 0},
		{-sin(DegreesToRadians(angle)), cos(DegreesToRadians(angle)), 0},
		{0, 0, 1}
	};

	transformToPoint = Multiply(transformToPoint, transformAngle);
	transformToPoint = Multiply(transformToPoint, transformFromPoint);

	for (int i = 0; i < vectorToRotate.size(); i++)
	{
		vector<vector<float>> wrapper;
		wrapper.push_back(vectorToRotate[i]);
		vectorToRotate[i] = Multiply(wrapper, transformToPoint)[0];
	}
}

bool CMath::bIsMatrix(vector<vector<float>>& vectorToCheck)
{
	int lastSize = vectorToCheck[0].size();
	for (vector<float> row : vectorToCheck)
	{
		if ((int)row.size() != lastSize)
		{
			return false;
		}
		lastSize = row.size();
	}
	return true;
}

float CMath::DegreesToRadians(float degrees)
{
	return degrees * M_PI / 180.f;
}

int CMath::RandBetween(int min, int max)
{
	return rand() % (max - min + 1) + min;
}
