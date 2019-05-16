#pragma once

struct RGB
{
	RGB(unsigned char r, unsigned char  g, unsigned char b)
	{
		pixelData[0] = r;
		pixelData[1] = g;
		pixelData[2] = b;
	}
	unsigned char pixelData[3];
};