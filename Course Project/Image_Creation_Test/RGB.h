#pragma once

struct RGB
{
	RGB(unsigned char r, unsigned char  g, unsigned char b)
	{
		
		R = r;
		G = g;
		B = b;

		pixelData[0] = r;
		pixelData[1] = g;
		pixelData[2] = b;
	}
	unsigned char pixelData[3];
	unsigned char  R;
	unsigned char G;
	unsigned char B;

};