#include "PROTO_Image.h"
#include <string>
#include <iostream>
#include <array>
using namespace std;


Image::~Image()
{
	delete[] rawData;
}

Image::Image(string fileName) :file_name(fileName)
{
	rawData = nullptr;
	for (int i = 0; i < 256; ++i)
	{
		reds.push_back(0);
		greens.push_back(0);
		blues.push_back(0);

		p_red.push_back(0);
		p_green.push_back(0);
		p_blue.push_back(0);
	}
	if (valid_header(fileName))
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
	rawData = _rawData;
}

void Image::writeFile(string fileName)
{
	cout << "Writing to file..." << endl;
	ofstream file;
	file.open(fileName, ios::binary | ios::out);
	writeHeader(file, magicNumber, height, width, max_color_val);
	file << rawData;
	file.close();

}

void Image::writeHeader(std::ofstream & file, string magicNumber, size_int height, size_int width, int max_col_val)
{
	file << magicNumber << std::endl;
	file << std::to_string(width) << std::endl << std::to_string(height) << std::endl;
	file << std::to_string(max_col_val) << std::endl;
}

//void Image::writePixelData(std::ofstream & file, RGB pixel)
//{
//	for (int p = 0; p < 3; p++)
//	{
//		if (pixel.pixelData[p] == 0)
//		{
//			file << " ";
//		}
//		else
//		{
//			file << pixel.pixelData[p];
//		}
//	}
//}

bool Image::valid_header(string fileName)
{
	std::ifstream file;
	file.open(fileName, std::ios::in | ios::binary);
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
		std::cout << "Valid file" << endl;
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

void Image::convertToGrayScale()
{
	cout << "Converting to graysacle, please wait..." << endl;
	for (int i = 0; i < getImageData().size(); ++i) {

		cout << i << endl;
		image_data[i].grayscale_average();
	}
	//rewriteRawData();
}

void Image::convertToMonochrome()
{
	cout << "Converting to monochrome, please wait..." << endl;
	for (int i = 0; i < getImageData().size(); ++i) {

		cout << i << endl;
		image_data[i].monochrome();
	}
	rewriteRawData();
}

void Image::generateHistogram()
{
	cout << "Generating histogram..." << endl;
	generatePercentages();
	vector<vector<RGB>> histogramData;
	histogramData.reserve(256);
	
	vector<RGB> backgroundCol;
	backgroundCol.reserve(100);
	for (int i = 0; i < 100; ++i)
	{
		backgroundCol.push_back(RGB(15, 15, 15,1));
	}
	for (int y = 0; y < 256; ++y)
	{
		histogramData.push_back(backgroundCol);	
	}

	for (int i = 0; i < 256; ++i)
	{
		histogramData[i][99] = RGB(255, 186, 1, 1);
	}

	for (int i = 0; i < 100; ++i)
	{
		histogramData[0][i] = RGB(255, 186, 1, 1);
	}


	for (int i = 0; i < 256; i++)
	{
		
		for (int j = 98; j > abs(98- p_red[i]); --j)
		{
			histogramData[i][j] = RGB(255, 1, 1, 1);
		}
		
	}
	string mainPath = "D:\\Documents\\Learning\\Object Oriented Programming\\Course Project\\OOP-Course-Project-S1\\saves\\Histogram_Test.ppm";

	char* rawData = new char[100 * 256*3];
	//char** rawD = new char[256][100];
	int rawIndex = 0;
	ofstream file;
	file.open(mainPath, ios::binary | ios::out);
	file << "P6" << endl;
	file << 256 << endl << 100 << endl;
	file << "255" << endl;
	for (int y = 0; y < 100; ++y)
	{
		for (int x = 0; x < 256; ++x)
		{/*
			rawData[rawIndex] = histogramData[x][y].pixelData[0];
			rawData[rawIndex+1] = histogramData[x][y].pixelData[1];
			rawData[rawIndex+2] = histogramData[x][y].pixelData[2];

			rawIndex+=3;*/
			file << histogramData[x][y].pixelData[0] << histogramData[x][y].pixelData[1]<< histogramData[x][y].pixelData[2];

		}
	}
	
	file << rawData;
	file.close();
}

void Image::generatePercentages()
{
	cout << "Generating percentages..." << endl;
	
	for (int i = 0; i < 256; ++i)
	{
		p_red.at(i) = (getReds().at(i) / (height*width)) * 100;
		p_green.at(i) = (getGreens().at(i)/ (height*width)) * 100;
		p_blue.at(i) = (getBlues().at(i)/(height*width)) * 100;
	}
	for (int i = 0; i < 256; ++i)
	{
		cout << i << " "<< p_red.at(i) << endl ;
	}
}

void Image::rewriteRawData()
{
	cout << "Reading data... "<< endl;
	delete[] rawData;
	rawData = new  char[getImageData().size() * 3];
	int rawDataIndex = 0;
	for (int i = 0; i < getImageData().size(); i++)
	{
		//cout << i << endl;
		rawData[rawDataIndex] = getImageData().at(i).pixelData[0];
		rawData[rawDataIndex + 1] = getImageData().at(i).pixelData[1];
		rawData[rawDataIndex + 2] = getImageData().at(i).pixelData[2];
		rawDataIndex += 3;
	}
	cout << strlen(rawData) << "NEW RAW SIZE" << endl;

}

void Image::readPixelData(string  fileName)
{
	cout << "Reading file..." << endl;
	std::ifstream file;
	file.open(fileName, ios::in | ios::ate | ios::binary);

	streampos size = file.tellg();
	char* memBlock;

	if (file.is_open())
	{
		size = file.tellg();
		cout << size << endl;
		memBlock = new char[size];
		file.seekg(0, ios::beg);
		file.read(memBlock, size);

		int spaces = 0;
		streampos headerLength = 0;


		for (int i = 0; i < size; i++)
		{
			if (spaces < 4)
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

		cout << size - headerLength << endl;
		rawData = memBlock;
		image_data.reserve(size);
		cout << memBlock[14] << "MEM BLOCK 14" << endl;
		unsigned long imageLen = size - headerLength;
		unsigned long modifier = (static_cast<unsigned long>(size) - imageLen);
		unsigned long imageSize = 2 * static_cast<unsigned long>(size) - imageLen - headerLength;
		cout << imageLen << "image_len" << endl;
		cout << "modifier" << (size -= imageLen) << endl;
		int cycles = 0;

		rawData = new char[imageSize];
		int rawDataIndex = 0;

		int avrg;
		for (unsigned long i = headerLength; i < imageSize; i += 3)
		{
			unsigned char R = memBlock[i];
			unsigned char G = memBlock[i+1];
			unsigned char B = memBlock[i+2];
			
			rawData[rawDataIndex] = R;
			rawData[rawDataIndex + 1] = G;
			rawData[rawDataIndex + 2] = B;

			reds.at(R) += 1;
			blues.at(B) += 1;
			greens.at(B) += 1;
			
			avrg = (R + G + B) / 3;
			RGB currentPixel(R, G, B, avrg);
			addPixel(currentPixel);
			rawDataIndex += 3;
			cycles++;
		}
		cout << image_data.size() << "SIZE" << endl;
		cout << cycles << "CYCLES" << endl;
		file.close();
	}
}


