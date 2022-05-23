#include "Painter.h"
#include <corecrt_math.h>

Painter::Painter()
{
	buffer[1][1];
}

void Painter::DrawLine(float x1f, float y1f, float x2f, float y2f, int color)
{
	/*if (x1 > x2 && y1> y2)
	{
		
	}
	
	if (x1 > x2 && y1 < y2)
	{
		float k = (y2 - y1) / (x2 - x1);
		float y = y1;
		for (float x = x1; x <= x2; x += 1.f, y += k)
		{
			buffer[(int)roundf(x1)][(int)roundf(y)] = color;
		}
	}

	if (x1 < x2 && y1 > y2)
	{
		float k = (y1 - y2) / (x2 - x1);
		float y = y2;
		for (float x = x1; x <= x2; x += 1.f, y += k)
		{
			buffer[(int)roundf(x1)][(int)roundf(y)] = color;
		}
	}

	if (x1 < x2 && y1 < y2)
	{
		float k = (y2 - y1) / (x2 - x1);
		float y = y1;
		for (float x = x1; x <= x2; x += 1.f, y += k)
		{
			buffer[(int)roundf(x1)][(int)roundf(y)] = color;
		}
	}*/

	int x1 = (int)roundf(x1f);
	int x2 = (int)roundf(x2f);
	int y1 = (int)roundf(y1f);
	int y2 = (int)roundf(y2f);

	const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    buffer[y2][x2] = color;
    while(x1 != x2 || y1 != y2) 
    {
		buffer[y1][x1];
        int error2 = error * 2;
        if(error2 > -deltaY) 
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) 
        {
            error += deltaX;
            y1 += signY;
        }
    }
}

void Painter::DrawLineSequence(vector<vector<float>> sequence, int color)
{
	for (int i = 1; i< sequence.size(); i++)
	{
		DrawLine(sequence[i-1][0], sequence[i - 1][1], sequence[i][0], sequence[i][1], color);
	}
	DrawLine(sequence[0][0], sequence[0][1], sequence[sequence.size()-1][0], sequence[sequence.size()-1][1], color);
}
