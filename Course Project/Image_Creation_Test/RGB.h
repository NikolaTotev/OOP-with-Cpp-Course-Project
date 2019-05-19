#pragma once
#include <ostream>
#include <iostream>

class RGB
{
public:
	RGB()
	{
		pixelData[0] = 1;
		pixelData[1] = 1;
		pixelData[2] = 1;
		avrg_value = 1;
	}
	RGB(unsigned char r, unsigned char  g, unsigned char b, int avrg)
	{
		pixelData[0] = r;
		pixelData[1] = g;
		pixelData[2] = b;
		avrg_value = avrg_value;
	}
	unsigned char pixelData[3];
	int avrg_value;

	void grayscale_average()
	{
		int avrg = (pixelData[0] + pixelData[1] + pixelData[2]) / 3;

		pixelData[0] = avrg;
		pixelData[1] = avrg;
		pixelData[2] = avrg;
	}

	void monochrome()
	{
		int avrg = (pixelData[0] + pixelData[1] + pixelData[2]) / 3;
		int limit = 128;
		int zero = 0;
		int twoFF = 255;
		if(avrg < 128)
		{
			pixelData[0] = 1;
			pixelData[1] = 1;
			pixelData[2] = 1;
			return;
		}

		pixelData[0] = 255;
		pixelData[1] = 255;
		pixelData[2] = 255;
	}

	const friend std::ostream& operator << (std::ostream& os, const RGB out)
	{
		os << out.pixelData[0] << out.pixelData[1] << out.pixelData[2];
		return os;
	}

	bool operator ==(const RGB& rhs)
	{
		return (pixelData[0] == rhs.pixelData[0] && pixelData[1] == rhs.pixelData[1] && pixelData[2] == rhs.pixelData[2]);
	}
	RGB& operator =(const RGB& rhs)
	{
		if(this!= &rhs)
		{
			pixelData[0] = rhs.pixelData[0];
			pixelData[1] = rhs.pixelData[1];
			pixelData[2] = rhs.pixelData[2];
		}
		return  *this;
	}
};
