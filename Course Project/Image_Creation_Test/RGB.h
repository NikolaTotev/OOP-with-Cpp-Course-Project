#pragma once
#include <ostream>
#include <iostream>

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
		int newRed = pixelData[0] * 0.3;
		int newGreen = pixelData[1] * 0.59;
		int newBlue = pixelData[2] * 0.11;

		pixelData[0] = newRed;
		pixelData[1] = newGreen;
		pixelData[2] = newBlue;
	}

	void grayscale_average()
	{
		/*	std::cout << "BEFORE" << std::endl;

			std::cout << pixelData[0] << std::endl;
			std::cout << pixelData[1] << std::endl;
			std::cout << pixelData[2] << std::endl;*/

		int avrg = (pixelData[0] + pixelData[1] + pixelData[2]) / 3;

		pixelData[0] = avrg;
		pixelData[1] = avrg;
		pixelData[2] = avrg;

		/*std::cout << "AFTER" << std::endl;
		std::cout << pixelData[0] << std::endl;
		std::cout << pixelData[1] << std::endl;
		std::cout << pixelData[2] << std::endl;
*/
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
};
