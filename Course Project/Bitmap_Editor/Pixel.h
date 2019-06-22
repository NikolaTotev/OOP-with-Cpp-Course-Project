#pragma once
#include <ostream>

class Pixel
{
	const int ZERO = 0;
	unsigned char pixelData[3];
	int avrg_value;

public:

	///Constructors & operators
	Pixel();
	Pixel(unsigned char r, unsigned char  g, unsigned char b, int avrg);
	Pixel(const Pixel& rhs);
	Pixel& operator =(const Pixel& rhs);
	bool operator ==(const Pixel& rhs);
	const friend std::ostream& operator << (std::ostream& os, const Pixel out);
	~Pixel();

	///Setters
	void setPixel(unsigned char r, unsigned char g, unsigned char b);
	void setPixel(unsigned char r, unsigned char g, unsigned char b, unsigned char avrg);

	///Getters
	const unsigned char* getPixel() { return pixelData; }
	int getAverage() { return avrg_value; }

	///Main functionality functions
	void toGrayscale();
	void toMonochrome(int limit = 128);

	
};

