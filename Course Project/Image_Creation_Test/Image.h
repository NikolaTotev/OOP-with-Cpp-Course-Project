#pragma once
#include  "RGB.h"
#include <vector>
#include <fstream>
using std::vector;
using std::string;
class Image
{
	typedef unsigned int size_int;

	unsigned int width;
	unsigned int height;
	const int max_color_val;
	vector<vector<RGB>> image_data;
	string magicNumber;
	string file_name;

public:

	Image(size_int width, size_int height, int maxColVal, string fileName, string magicNumber) :
		width(width), height(height), max_color_val(maxColVal), magicNumber(magicNumber)
	{
		setFileName(fileName);
	}

	//TODO implement option to add any extention based on input parameter;
	void setFileName(string new_name) { file_name = new_name+".ppm";}
	
	string getFileName() { return file_name; }
	string getMagicNumber() { return magicNumber; }

	size_int getHeight() { return height; }
	size_int getWidth() { return  width; }

	int getColorValue() { return max_color_val; }


	void writeHeader(std::ofstream& file, string magicNumber, size_int height, size_int width, int max_col_val);
	void writePixelData(std::ofstream& file, RGB pixel);

	void readHeader(string file);
	void readPixelData(std::ifstream& file);
};
