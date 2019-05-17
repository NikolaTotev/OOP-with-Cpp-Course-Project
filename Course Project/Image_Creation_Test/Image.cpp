#include "Image.h"
#include <string>
#include <iostream>
using namespace std;


Image::~Image()
{
	delete[] rawData;
}

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

void Image::setRawImageData(char * _rawData)
{
	
}

void Image::writeFile(std::ofstream& file)
{
	//file << rawData;

	for (int i = 0; i < static_cast<int>(getImageData().size()); i++)
	{
		file << getImageData().at(i).pixelData[0];
		file << getImageData().at(i).pixelData[1];
		file << getImageData().at(i).pixelData[2];
		//cout << i<< "w" <<endl;
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
	file.open(fileName, std::ios::in|ios::binary);
	string magicNumber;
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
		std::cout << "Valid file" <<endl;
		return true;
	}
	file.close();
	//std::cout << magicNumber << std::endl << width << std::endl << height << std::endl << maxColVal << std::endl;
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
	file.open(fileName, ios::in | ios::ate | ios::binary);	
	
	streampos size = file.tellg();
	char* memBlock;

	if(file.is_open())
	{
		size = file.tellg();
		cout << size << endl;
		memBlock = new char[size];
		file.seekg(0, ios::beg);
		file.read(memBlock, size);

		int spaces = 0;
		streampos headerLength =0;
		

		for (int i =0; i< size; i ++)
		{
			if(spaces <4)
			{
				if (memBlock[i] == '\n')
				{
					spaces++;
				}
				headerLength += 1;
			}
			else
			{
				break;
			}
		}
		cout << spaces << "SPACES" << endl;
		
		cout << size-headerLength << endl;
		rawData = memBlock;
		image_data.reserve(size);
		cout << memBlock[14] << "MEM BLOCK 14" << endl;
		unsigned long imageLen = size - headerLength;
		unsigned long modifier = (static_cast<unsigned long>(size) - imageLen);
		cout << imageLen << "image_len" << endl;
		cout << "modifier" << (size -= imageLen) << endl;
		int cycles = 0;
		for (unsigned long i = headerLength; i < (imageLen+(modifier)); i += 3)
		{
			//std::cout << i << "r" << std::endl;
			cycles++;
			RGB currentPixel(memBlock[i], memBlock[i+1], memBlock[i+2]);
			addPixel(currentPixel);
		}
		cout << image_data.size() << "SIZE"<< endl;
		cout << cycles << "CYCLES"<< endl;
	}	
}
