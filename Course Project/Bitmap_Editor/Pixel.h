#pragma once
#include <ostream>

class Pixel
{
	const int ZERO = 0;

	unsigned char pixelData[3];
	int avrg_value;

public:
	Pixel();
	Pixel(unsigned char r, unsigned char  g, unsigned char b, int avrg);
	~Pixel();

	void setPixel(int r, int g, int b);
	void setPixel(int r, int g, int b, int avrg);

	int getAverage() { return avrg_value; }
	
	void toGrayscale();
	void toMonochrome(int limit = 128);

	const friend std::ostream& operator << (std::ostream& os, const Pixel out);
	bool operator ==(const Pixel& rhs);
	Pixel& operator =(const Pixel& rhs);
	
};

