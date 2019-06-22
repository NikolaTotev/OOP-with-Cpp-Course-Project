#include "Pixel.h"



Pixel::Pixel()
{
	setPixel(ZERO, ZERO, ZERO, ZERO);
}

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b, int avrg)
{
	setPixel(r, g, b, avrg);
}

Pixel::Pixel(const Pixel& rhs)
{
	pixelData[0] = rhs.pixelData[0];
	pixelData[1] = rhs.pixelData[1];
	pixelData[2] = rhs.pixelData[2];
	avrg_value = rhs.avrg_value;
}


Pixel& Pixel::operator=(const Pixel& rhs)
{
	if (this != &rhs)
	{
		pixelData[0] = rhs.pixelData[0];
		pixelData[1] = rhs.pixelData[1];
		pixelData[2] = rhs.pixelData[2];
		avrg_value = rhs.avrg_value;
	}
	return  *this;
}

Pixel::~Pixel()
{
}


const std::ostream& operator<<(std::ostream& os, const Pixel out)
{
	os << out.pixelData[0] << out.pixelData[1] << out.pixelData[2];
	return os;
}

bool Pixel::operator==(const Pixel& rhs)
{
	return (pixelData[0] == rhs.pixelData[0] && pixelData[1] == rhs.pixelData[1] && pixelData[2] == rhs.pixelData[2]);
}


void Pixel::setPixel(unsigned char r, unsigned char g, unsigned char b)
{
	pixelData[0] = r;
	pixelData[1] = g;
	pixelData[2] = b;
}


void Pixel::setPixel(unsigned char r, unsigned char g, unsigned char b, unsigned char avrg)
{
	setPixel(r, g, b);
	avrg_value = avrg;
}

void Pixel::toGrayscale()
{	
	setPixel(avrg_value, avrg_value, avrg_value);
}

void Pixel::toMonochrome(int limit)
{
	if (getAverage() < limit)
	{
		setPixel(1,1, 1);
		return;
	}
	setPixel(255, 255, 255);
}







