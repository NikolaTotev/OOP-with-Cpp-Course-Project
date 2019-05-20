#pragma once
#include <string>
#include "Pixel.h"
#include <vector>

class Image
{
public:
	enum formats { PPM, PBM, PGM, NA };
private:
	const int c_default_width = 256;
	const int c_default_height = 256;
	typedef  unsigned int size_int;

	formats format;

	std::string file_name;
	std::string magic_number;
	size_int width;
	size_int height;
	int bitDepth;
	std::vector<Pixel> image_data;
	char* raw_data;

	std::vector<float> red_count;
	std::vector<float> green_count;
	std::vector<float> blue_count;

	std::vector<float> red_percent;
	std::vector<float> green_percent;
	std::vector<float> blue_percent;

	void init_vectors_256();
	formats determine_format(std::string fileName);
	bool validHeader(std::string fileName);

public:

	Image(std::string fileName);
	~Image();

	void setFileName(std::string _fileName) { file_name = _fileName; }
	void setMagicNumber(std::string _magicNumber) { magic_number = _magicNumber; }
	void setWidth(size_int _width) { width = _width; }
	void setHeight(size_int _height) { height = _height; }
	void setBitDepth(int _depth) { bitDepth = _depth; }

};

