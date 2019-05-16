#include "Image.h"
#include <string>
#include <iostream>

Image::Image(string fileName) :file_name(fileName)
{
	if (validHeader(fileName))
	{
		readPixelData(fileName);
	}
	else
	{
		setHeaderInfo("P6", defaultWidth, defaultHeight, default_ppm_depth);
	}
}

void Image::writeFile(std::ofstream& file)
{
	for (int i = 0; i < static_cast<int>( getImageData().size()); i++)
	{
		std::cout << "WRITING TO FILE";
		file << getImageData().at(i).pixelData[0];
		file << getImageData().at(i).pixelData[1];
		file << getImageData().at(i).pixelData[2];
	}
}

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

bool Image::validHeader(string fileName)
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

	file >> magicNumber >> width >> height >> maxColVal;

	bool isValidFormat = (magicNumber == "P6" | magicNumber == "P5" | magicNumber == "P4");
	bool hasValidSize = (width > 0 && height > 0);
	bool hasValidBitDepth = (maxColVal > 0 && maxColVal < 256);

	if (isValidFormat && hasValidSize && hasValidBitDepth)
	{
		setHeaderInfo(magicNumber, width, height, maxColVal);
		std::cout << "Valid file";
		return true;
	}
	file.close();
	std::cout << magicNumber << std::endl << width << std::endl << height << std::endl << maxColVal << std::endl;
	return false;
}

void Image::setHeaderInfo(string magicNumber, size_int width, size_int height, int bitDepth)
{
	setMagicNumber(magicNumber);
	setWidth(width);
	setHeight(height);
	setBitDepth(bitDepth);
}

void Image::readPixelData(string  fileName)
{
	std::ifstream file;
	file.open(fileName);	
	string sacrificial;
	string imageData;
	file >> sacrificial >> sacrificial >> sacrificial >> sacrificial;
	char c;

	while (true) {
		c = file.get();
		if (!file){
		break;
		}
		imageData.push_back(c);
		std::cout << c;
		
	}

	setRawImageData(imageData);
	file.close();

	setRawImageData(imageData);

	std::cout << getRawImageData().length() << std::endl;
	std::cout << getHeight()*getWidth() << std::endl;

	for (unsigned long i = 1; i < getRawImageData().size()-3; i+=3)
	{
		std::cout << "PLUS 0" << i << std::endl;
		
	RGB currentPixel(getRawImageData().at(i), getRawImageData().at(i+2), getRawImageData().at(i+3));
		
	addPixel(currentPixel);		
	}
	std::cout << getImageData().size() << "SIZE" << std::endl;
}
