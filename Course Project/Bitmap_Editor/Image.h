#pragma once
#include <string>
#include "Pixel.h"
#include <vector>
#include <thread>
#include  "Job.h"

class Image
{
public:
	enum formats { PPM, PBM, PGM, NA };
	enum ops { monochrome, grayscale, histogram };

private:
	const int c_default_width = 256;
	const int c_default_height = 256;
	typedef  unsigned int size_int;
	bool isGrayscale = true;
	bool isMonochrome = true;

	formats format;

	std::string file_name = "";
	std::string magic_number = "";
	size_int width = 0;
	size_int height = 0;
	int bitDepth = 0;
	std::vector<Pixel> image_data;
	//char* raw_data;
	std::vector<char>raw_data;

	std::vector<float> red_count;
	std::vector<float> green_count;
	std::vector<float> blue_count;

	std::vector<float> red_percent;
	std::vector<float> green_percent;
	std::vector<float> blue_percent;

	std::vector<std::thread> tasks;
	std::vector<ops> operations;
	std::vector<Job::args_enum> op_args;

	void init_vectors_256();
	formats determine_format(std::string fileName);
	bool valid_header(std::string fileName);
	void read_image(std::string fileName);
	void update_raw_data(formats format);
	const void write_to_file(std::string path);
	void copy(const Image& rhs);
	void showProgress(int fullTask, int completed);
	void executeTasks();
public:

	Image(std::string fileName);
	~Image();

	void setFileName(std::string _fileName) { file_name = _fileName; }
	void setMagicNumber(std::string _magicNumber) { magic_number = _magicNumber; }
	///<summary>
	///TEST
	///<para> TEST TEST
	///</summary>
	void setWidth(size_int _width) { width = _width; }
	void setHeight(size_int _height) { height = _height; }
	void setBitDepth(int _depth) { bitDepth = _depth; }
	void toGrayscale();
	void toMonochrome();
	void genHistogram(Job::args_enum target_color);
	void generatePercentages();
	void add_operation(ops op,  Job::args_enum = Job::args_enum::NA);

	void begin_work();

	std::vector<float> getReds() const { return red_count; }
	std::vector<float> getBlues() const { return blue_count; }
	std::vector<float> getGreens() const { return green_count; }

	std::vector<float> getRed_percentage() const { return red_percent; }
	std::vector<float> getBlue_percentage() const { return blue_percent; }
	std::vector<float> getGreen_percentage() const { return green_percent; }

	std::vector<Pixel> getImageData() { return image_data; };

	Image& operator =(const Image& rhs);
	Image(const Image& rhs);
};

