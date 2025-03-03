#pragma once
#include  "RGB.h"
#include <vector>
#include <fstream>
using std::vector;
using std::string;
class Image
{
	typedef unsigned int size_int;
	const size_int defaultWidth = 512;
	const size_int defaultHeight = 512;
	const size_int default_ppm_depth = 255;


	unsigned int width;
	unsigned int height;
	int max_color_val;

	vector<RGB> image_data;
	char* rawData;
	string magicNumber;
	string file_name;

	vector<float> reds;
	vector<float> blues;
	vector<float> greens;

	vector<float> p_red;
	vector<float> p_green;
	vector<float> p_blue;
public:
	std::ofstream file;
	~Image();
	Image(size_int width, size_int height, int maxColVal, string fileName, string magicNumber) :
		width(width), height(height), max_color_val(maxColVal), magicNumber(magicNumber)
	{
		set_file_name(fileName);
		rawData = nullptr;
		reds.reserve(256);
		greens.reserve(256);
		blues.reserve(256);

		for (int i = 0; i < 256; ++i)
		{
			reds.push_back(0);
			greens.push_back(0);
			blues.push_back(0);

			p_red.push_back(0);
			p_green.push_back(0);
			p_blue.push_back(0);
		}
	}

	Image(string fileName);

	//TODO implement option to add any extention based on input parameter;
	void set_file_name(string new_name) { file_name = new_name + ".ppm"; }

	void set_magic_number(string _magicNumber) { magicNumber = _magicNumber; }
	void set_height(size_int _height) { height = _height; }
	void set_width(size_int _width) { width = _width; }
	void set_bit_depth(int _depth) { max_color_val = _depth; }
	void setRawImageData(char* _rawData);
	void addPixel(RGB pixel) { image_data.push_back(pixel); }
	void writeFile(string file);
	string getFileName() { return file_name; }
	string getMagicNumber() { return magicNumber; }

	void setImageData(vector<RGB> newData) { image_data = newData; }

	size_int getHeight() { return height; }
	size_int getWidth() { return  width; }

	vector<RGB> getImageData() { return image_data; }
	char* getRawImageData() { return rawData; }

	vector<float> getReds() const { return reds; }
	vector<float> getBlues() const { return blues; }
	vector<float> getGreens() const { return greens; }

	vector<float> getRed_percentage() const { return p_red; }
	vector<float> getBlue_percentage() const { return p_blue; }
	vector<float> getGreen_percentage() const { return p_green; }

	int getColorValue() { return max_color_val; }


	void writeHeader(std::ofstream& file, string magicNumber, size_int height, size_int width, int max_col_val);
	//void writePixelData(std::ofstream& file, RGB pixel);

	bool validHeader(string file);
	void readPixelData(string file);

	void setHeaderInfo(string magicNumber, size_int width, size_int height, int bitDepth);

	void convertToGrayScale();
	void convertToMonochrome();

	void generateHistogram();
	void generatePercentages();

	void rewriteRawData();
};
