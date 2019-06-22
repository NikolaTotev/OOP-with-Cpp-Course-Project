#pragma once
#include <string>
#include "Pixel.h"
#include <vector>
#include  "Job.h"

class Image
{
public:
	///enum for all of the available formats. NA used when the format can't be determined.
	enum formats { PPM, PBM, PGM, NA };

	///enum for all of the available operations. Used for easier use of passed in commands.
	enum ops { monochrome, grayscale, histogram };

private:
	///Typdef used for the size of the image.
	typedef  unsigned int size_int;

	///Default constants
	const int c_default_width = 256;
	const int c_default_height = 256;

	///General image information variables
	bool isGrayscale = true;
	bool isMonochrome = true;
	formats format;

	///Header variables
	std::string file_name = "";
	std::string magic_number = "";
	size_int width = 0;
	size_int height = 0;
	int bitDepth = 0;

	///Image data variables
	std::vector<char>raw_data;
	std::vector<Pixel> image_data;

	///Histogram calculation variables
	std::vector<float> red_count;
	std::vector<float> green_count;
	std::vector<float> blue_count;

	///Operation variables
	std::vector<ops> operations;
	std::vector<Job::args_enum> op_args;

	///Initialization functions
	void initVectors();

	///Header validation & format checks.
	formats determineFormat(std::string fileName);
	bool validHeader(std::string fileName);

	///Read/write functions
	void readImage(std::string fileName);
	void updateRawData(formats format);
	const void writeToFile(std::string fileName);

	///Copy function used in copy constructor.
	void copy(const Image& rhs);

	///Operation execution.
	void executeTasks()const;
public:

	///Constructor & redefined operators.
	Image(std::string fileName);
	Image(const Image& rhs);
	Image& operator =(const Image& rhs);
	~Image();

	///Header setters.
	void set_file_name(std::string _fileName) { file_name = _fileName; }
	void set_magic_number(std::string _magicNumber) { magic_number = _magicNumber; }
	void set_width(size_int _width) { width = _width; }
	void set_height(size_int _height) { height = _height; }
	void set_bit_depth(int _depth) { bitDepth = _depth; }

	///Getter for retrieving image data.
	std::vector<Pixel> get_image_data() { return image_data; };

	///Main program functionality.
	void to_grayscale()const;
	void to_monochrome() const;
	void gen_histogram(Job::args_enum target_color)const ;

	///Functions for operation execution
	void add_operation(ops op,  Job::args_enum = Job::args_enum::NA);
	void begin_work();

	///Getters for getting vectors containing information about color data.
	std::vector<float> getReds() const { return red_count; }
	std::vector<float> getBlues() const { return blue_count; }
	std::vector<float> getGreens() const { return green_count; }


};

