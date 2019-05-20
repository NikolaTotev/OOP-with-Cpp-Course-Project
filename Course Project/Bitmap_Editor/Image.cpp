#include "Image.h"
#include <iostream>
#include <fstream>


void Image::init_vectors_256()
{
	red_count.reserve(256);
	green_count.reserve(256);
	blue_count.reserve(256);

	red_percent.reserve(256);
	green_percent.reserve(256);
	blue_percent.reserve(256);

	for (int i = 0; i < 256; ++i)
	{
		red_count.push_back(0);
		green_count.push_back(0);
		blue_count.push_back(0);


		red_percent.push_back(0);
		green_percent.push_back(0);
		blue_percent.push_back(0);
	}
}

Image::formats Image::determine_format(std::string fileName)
{

	int sub_index = strlen(fileName.c_str()) - 3;
	std::string format = fileName.substr(sub_index);

	if (format == "ppm")return PPM;
	if (format == "pgm")return PGM;
	if (format == "pbm")return PBM;
	return NA;
}

bool Image::validHeader(std::string fileName)
{
	std::ifstream file;
	file.open(fileName, std::ios::in | std::ios::binary);
	std::string magicNumber;
	size_int width;
	size_int height;
	int bitDepth;

	file >> magicNumber >> width >> height >> bitDepth;

	bool isValidFormat = (magicNumber == "P6" | magicNumber == "P5" | magicNumber == "P4");
	bool hasValidSize = (width > 0 && height > 0);
	bool hasValidBitDepth = (bitDepth > 0 && bitDepth < 256);

	if (isValidFormat && hasValidSize && hasValidBitDepth)
	{
		setFileName(fileName);
		setMagicNumber(magicNumber);
		setWidth(width);
		setHeight(height);
		setBitDepth(bitDepth);
		return true;
	}

	file.close();
	return false;
}

Image::Image(std::string fileName)
{
	format = determine_format(fileName);
	init_vectors_256();

}


Image::~Image()
{
}
