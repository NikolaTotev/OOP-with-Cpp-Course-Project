#pragma once
#include <string>
#include "Pixel.h"
#include <vector>
#include <thread>

class Image
{
public:
	enum formats { PPM, PBM, PGM, NA };
private:
	const int c_default_width = 256;
	const int c_default_height = 256;
	typedef  unsigned int size_int;

	formats format;

	std::string file_name = "";
	std::string magic_number = "";
	size_int width = 0;
	size_int height = 0;
	int bitDepth = 0;
	std::vector<Pixel> image_data;
	char* raw_data;

	std::vector<float> red_count;
	std::vector<float> green_count;
	std::vector<float> blue_count;

	std::vector<float> red_percent;
	std::vector<float> green_percent;
	std::vector<float> blue_percent;

	std::vector<std::thread> tasks;

	void init_vectors_256();
	formats determine_format(std::string fileName);
	bool valid_header(std::string fileName);
	void read_image(std::string fileName);
	void update_raw_data();
	const void write_to_file(std::string path);
	void copy(const Image& rhs);
	void showProgress(int fullTask, int completed);
public:

	Image(std::string fileName);
	~Image();

	void setFileName(std::string _fileName) { file_name = _fileName; }
	void setMagicNumber(std::string _magicNumber) { magic_number = _magicNumber; }
	void setWidth(size_int _width) { width = _width; }
	void setHeight(size_int _height) { height = _height; }
	void setBitDepth(int _depth) { bitDepth = _depth; }
	void toGrayscale();
	void toMonochrome();

	std::vector<Pixel> getImageData() { return image_data; };

	Image& operator =(const Image& rhs);
	Image(const Image& rhs);
};

