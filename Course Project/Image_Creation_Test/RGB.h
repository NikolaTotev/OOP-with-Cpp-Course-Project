#pragma once
#include <ostream>

class RGB
{
public:
	RGB(unsigned char r, unsigned char  g, unsigned char b)
	{
		pixelData[0] = r;
		pixelData[1] = g;
		pixelData[2] = b;
	}
	unsigned char pixelData[3];

	void graysacle_weighted()
	{
		pixelData[0] *= 0.3;
		pixelData[1] *= 0.59;
		pixelData[2] *= 0.11;
	}

	void grayscale_average()
	{
		int avrg = (pixelData[0] + pixelData[1] + pixelData[2])/3;
		pixelData[0] = avrg;
		pixelData[1] = avrg;
		pixelData[2] = avrg;
	}

	const friend std::ostream& operator << (std::ostream& os, const RGB out) 
	{
		os << out.pixelData[0] << out.pixelData[1] << out.pixelData[2];
		return os;
	}
};
