#include "Painter.h"
#include <corecrt_math.h>

void Painter::DrawLine(float x1f, float y1f, float x2f, float y2f, uint32_t color)
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
    PutPixel(x2, y2, color);
    while(x1 != x2 || y1 != y2) 
    {
        PutPixel(x1, y1, color);
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

void Painter::DrawLineSequence(std::vector<std::vector<float>> sequence, uint32_t color, bool bIsCycled)
{
	for (int i = 1; i< sequence.size(); i++)
	{
		DrawLine(sequence[i-1][0], sequence[i - 1][1], sequence[i][0], sequence[i][1], color);
	}
    if(bIsCycled)
    {
		DrawLine(sequence[sequence.size() - 1][0], sequence[sequence.size() - 1][1], sequence[0][0], sequence[0][1], color);
    }
}

void Painter::PutPixel(int x, int y, uint32_t color)
{
    if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT) return;
    buffer[y][x] = color;
}

uint32_t Painter::RGBToUInt32(int r, int g, int b)
{
    return (uint32_t)r << 16 | (uint32_t)g << 8 | (uint32_t)b;
}


