#include "Image.h"
#include <string>
#include <iostream>

void Image::writeHeader(std::ofstream & file, string magicNumber, size_int height, size_int width, int max_col_val)
{
	file << magicNumber << std::endl;
	file << std::to_string(width) << std::endl << std::to_string(height) << std::endl;
	file << std::to_string(max_col_val) << std::endl;
}

void Image::writePixelData(std::ofstream & file, RGB pixel)
{
	for (int p = 0; p < 3; p++)
	{
		if (pixel.pixelData[p] == 0)
		{
			file << " ";
		}
		else
		{
			file << pixel.pixelData[p];
		}
	}
}

bool Image::readHeader(string fileName)
{
	std::ifstream file;
	file.open(fileName);
	string magicNumber;
	string cmnt;
	string cmnt1;
	string cmnt2;
	size_int width;
	size_int height;
	int maxColVal;
	string currentValue;

	file >> magicNumber >> width  >> height  >> maxColVal;

	bool isValidFormat = (magicNumber == "P6" | magicNumber == "P5" | magicNumber == "P4");
	bool hasValidSize = (width > 0 && height > 0);
	bool hasValidBitDepth = (maxColVal > 0 && maxColVal < 256);

	if(isValidFormat && hasValidSize && hasValidBitDepth)
	{
		std::cout << "Valid file";
	}
	else
	{
		std::cout << "File is invalid";
	}
	std::cout << magicNumber << std::endl << width << std::endl << height << std::endl << maxColVal << std::endl;

	file.close();
}
