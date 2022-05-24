#include "CMath.h"

#include <vector>
#include <iostream>
#include <corecrt_math_defines.h>
#include "Engine.h"
#include "Painter.h"

std::vector<std::vector<float>> CMath::Multiply(std::vector<std::vector<float>>& firstVector, std::vector<std::vector<float>>& secondVector)
{
	if (!bIsMatrix(firstVector) || !bIsMatrix(secondVector)) throw std::invalid_argument("One of vectors is not a matrix");
	int firstRows = (int)firstVector.size();
	int firstCols = (int)firstVector[0].size();
	int secondRows = (int)secondVector.size();
	int secondCols = (int)secondVector[0].size();

	if (firstCols != secondRows) throw std::invalid_argument("Cols of first vector doest match rows of second");
	std::vector<std::vector<float>> product(firstRows, std::vector<float>(secondCols));

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

void CMath::RotateAroundPoint(std::vector<std::vector<float>>& vectorToRotate, std::vector<float>& point, float angle)
{
	std::vector<std::vector<float>> transformToPoint{
		{1, 0, 0},
		{0, 1, 0},
		{-point[0], -point[1], 1}
	};

	std::vector<std::vector<float>> transformFromPoint{
		{1, 0, 0},
		{0, 1, 0},
		{point[0], point[1], 1}
	};

	std::vector<std::vector<float>> transformAngle{
		{cos(DegreesToRadians(angle)), sin(DegreesToRadians(angle)), 0},
		{-sin(DegreesToRadians(angle)), cos(DegreesToRadians(angle)), 0},
		{0, 0, 1}
	};

	transformToPoint = Multiply(transformToPoint, transformAngle);
	transformToPoint = Multiply(transformToPoint, transformFromPoint);

	for (int i = 0; i < vectorToRotate.size(); i++)
	{
		std::vector<std::vector<float>> wrapper;
		wrapper.push_back(vectorToRotate[i]);
		vectorToRotate[i] = Multiply(wrapper, transformToPoint)[0];
	}
}

bool CMath::bIsMatrix(std::vector<std::vector<float>>& vectorToCheck)
{
	int lastSize = vectorToCheck[0].size();
	for (std::vector<float> row : vectorToCheck)
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

std::vector<std::vector<float>> CMath::ExcludeSafeBounds(std::vector<std::vector<float>>& bounds, float xOutOfBounds, float yOutOfBounds)
{
	std::vector<std::vector<float>> temp = bounds;

	float maxLeft = SCREEN_WIDTH + xOutOfBounds ;
	std::vector<float> vMaxLeft;
	float maxRight = -xOutOfBounds;
	std::vector<float> vMaxRight;

	for(std::vector<float> point : temp)
	{
		if(point[0]<maxLeft)
		{
			maxLeft = point[0];
			vMaxLeft = point;
		}
		if (point[0] > maxRight)
		{
			maxRight = point[0];
			vMaxRight = point;
		}
	}

	float minHeight = vMaxRight[1] > vMaxLeft[1] ? vMaxLeft[1] : vMaxRight[1];

	int size = temp.size();
	for (int i = 0; i < size; i++)
	{
		if(temp[i][0]>maxLeft && temp[i][0]<maxRight && temp[i][1]<minHeight)
		{
			temp.erase(temp.begin() + i);
			i--;
			size--;
		}
	}
	SortByX(temp);
	return temp;
}

void CMath::SortByX(std::vector<std::vector<float>>& bounds)
{
	for (int i = 1; i < bounds.size(); i++)
		for (int j = i; j > 0 && bounds[j - 1][0] > bounds[j][0]; j--)
		{
			std::vector<float> temp = bounds[j - 1];
			bounds[j - 1] = bounds[j];
			bounds[j] = temp;
		}		
	int a = 0;
}

HitResult CMath::TraceByColor(float x1f, float y1f, float x2f, float y2f, uint32_t color)
{
	int x1 = (int)roundf(x1f);
	int x2 = (int)roundf(x2f);
	int y1 = (int)roundf(y1f);
	int y2 = (int)roundf(y2f);

	const int deltaX = abs(x2 - x1);
	const int deltaY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
	const int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	
	if(buffer[y2][x2] != color)
	{
		HitResult hit;
		hit.bHit = true;
		hit.hitObject = buffer[y2][x2];
		hit.hitPoint = Point(x2, y2);
		return hit;
	}
	//Painter::PutPixel(x2, y2, Painter::RGBToUInt32(255, 255, 0));

	while (x1 != x2 || y1 != y2)
	{	
		if (buffer[y1][x1] != color)
		{
			HitResult hit;
			hit.bHit = true;
			hit.hitObject = buffer[y1][x1];
			hit.hitPoint = Point(x1, y1);
			return hit;
		}
		//Painter::PutPixel(x1, y1, Painter::RGBToUInt32(255,255,0));
		int error2 = error * 2;
		if (error2 > -deltaY)
		{
			error -= deltaY;
			x1 += signX;
		}
		if (error2 < deltaX)
		{
			error += deltaX;
			y1 += signY;
		}
	}

	HitResult hit;
	hit.bHit = false;
	hit.hitObject = buffer[y1][x1];
	hit.hitPoint = Point(x1, y1);
	return hit;
}
