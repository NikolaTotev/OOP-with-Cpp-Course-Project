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

void Image::readHeader(string fileName)
{
	std::ifstream file;
	file.open(fileName);
	int numberOfTabs = 0;
	string magicNumber;
	string width;
	string height;
	string maxColVal;
	string currentValue;
	while(numberOfTabs < 4)
	{
		file >> currentValue;
		std::cout << currentValue;
		if(currentValue == " ")
		{
			std::cout << "SPACE";
			numberOfTabs++;
		}

		switch (numberOfTabs)
		{
		case(0):
			file >> magicNumber;
			break;
		case(1):
			file >> width;
			break;
		case(2):
			file >> height;
			break;
		case(3):
			file >> magicNumber;
			break;
		}
	}
	std::cout << magicNumber << std::endl << width << std::endl << height << std::endl << maxColVal << std::endl;

	file.close();
}
