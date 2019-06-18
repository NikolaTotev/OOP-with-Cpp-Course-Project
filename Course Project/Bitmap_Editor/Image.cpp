#include "Image.h"
#include <iostream>
#include <fstream>
#include <thread>
void Image::init_vectors_256()
{
	red_count.reserve(256);
	green_count.reserve(256);
	blue_count.reserve(256);

	red_percent.reserve(256);
	green_percent.reserve(256);
	blue_percent.reserve(256);

	for (int i = 0; i < 256; ++i)
	{
		red_count.push_back(0);
		green_count.push_back(0);
		blue_count.push_back(0);


		red_percent.push_back(0);
		green_percent.push_back(0);
		blue_percent.push_back(0);
	}
}

Image::formats Image::determine_format(std::string fileName)
{

	int sub_index = strlen(fileName.c_str()) - 3;
	std::string format = fileName.substr(sub_index);

	if (format == "ppm")return PPM;
	if (format == "pgm")return PGM;
	if (format == "pbm")return PBM;
	return NA;
}

bool Image::valid_header(std::string fileName)
{
	std::ifstream file;
	file.open(fileName, std::ios::in | std::ios::binary);
	std::string magicNumber;
	size_int width;
	size_int height;
	int bitDepth;

	file >> magicNumber >> width >> height >> bitDepth;

	bool isValidFormat = (magicNumber == "P6" | magicNumber == "P5" | magicNumber == "P4");
	bool hasValidSize = (width > 0 && height > 0);
	bool hasValidBitDepth = (bitDepth > 0 && bitDepth < 256);

	if (isValidFormat && hasValidSize && hasValidBitDepth)
	{
		setFileName(fileName);
		setMagicNumber(magicNumber);
		setWidth(width);
		setHeight(height);
		setBitDepth(bitDepth);
		return true;
	}

	file.close();
	return false;
}

void Image::read_image(std::string fileName)
{
	std::cout << "Reading file..." << std::endl;
	std::ifstream file;
	file.open(fileName, std::ios::in | std::ios::ate | std::ios::binary);

	std::streampos size = file.tellg();
	char* memBlock;

	if (file.is_open())
	{
		size = file.tellg();
		memBlock = new char[size];
		file.seekg(0, std::ios::beg);
		file.read(memBlock, size);

		int spaces = 0;
		std::streampos headerLength = 0;

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


		unsigned long imageLen = static_cast<unsigned long>(size) - headerLength;
		unsigned long modifier = (static_cast<unsigned long>(size) - imageLen);
		unsigned long imageSize = imageLen + modifier;

		image_data.reserve(size);
		raw_data = new char[imageSize];

		int rawDataIndex = 0;

		for (unsigned long i = headerLength; i < imageSize; i += 3)
		{
			unsigned char R = memBlock[i];
			unsigned char G = memBlock[i + 1];
			unsigned char B = memBlock[i + 2];

			raw_data[rawDataIndex] = R;
			raw_data[rawDataIndex + 1] = G;
			raw_data[rawDataIndex + 2] = B;

			red_count.at(R) += 1;
			blue_count.at(B) += 1;
			green_count.at(G) += 1;

			int avrg = (R + G + B) / 3;
			Pixel pixel(avrg, avrg, avrg, avrg);
			image_data.push_back(pixel);
			rawDataIndex += 3;
		}
		file.close();
	}
}

void Image::update_raw_data(formats format)
{
	std::cout << "Updating data... " << std::endl;
	//delete[] raw_data;
	switch (format) {
	case PPM:
		raw_data = new  char[image_data.size() * 3];
		std::cout << "PPM" << std::endl;
		break;
	case PBM:
		raw_data = new  char[image_data.size() * 3];
		break;
	case PGM:
		raw_data = new  char[image_data.size()];
		break;
	case NA:
		break;
	default:
		return;
	}

	int taskSize = image_data.size();
	int rawDataIndex = 0;
	for (int i = 0; i < taskSize; i++)
	{
		raw_data[rawDataIndex] = image_data.at(i).getPixel()[0];
		if (format == PPM || format == PBM)
		{
			raw_data[rawDataIndex + 1] = image_data.at(i).getPixel()[1];
			raw_data[rawDataIndex + 2] = image_data.at(i).getPixel()[2];
			rawDataIndex += 3;
		}
		else
		{
			rawDataIndex += 1;
		}
	}
}

const void Image::write_to_file(std::string path)
{
	std::cout << "Writing to file..." << std::endl;
	std::ofstream file;
	file.open(path, std::ios::binary | std::ios::out);
	file << magic_number << std::endl;
	file << width << std::endl << height << std::endl;
	file << bitDepth << std::endl;
	file.write(raw_data, strlen(raw_data));
	file.close();
}

void Image::copy(const Image& rhs)
{
	std::cout << "COPY CONST" << std::endl;
	file_name = rhs.file_name;
	width = rhs.width;
	height = rhs.height;
	magic_number = rhs.magic_number;
	bitDepth = rhs.bitDepth;
	image_data = rhs.image_data;
}

void Image::executeTasks()
{
	for (int i = 0; i < operations.size(); ++i)
	{
		if (operations[i] == monochrome)
		{
			std::thread mono_chrome(&Image::toMonochrome, this);
			mono_chrome.join();
		}
		if (operations[i] == grayscale)
		{
			std::thread gray_scale(&Image::toGrayscale, this);
			gray_scale.join();
		}
	}
}

void Image::add_operation(ops op, std::string args)
{
	operations.push_back(op);
}

void Image::begin_work()
{
	if (valid_header(file_name))
	{
		read_image(file_name);
		executeTasks();
	}
	else
	{
		std::cout << "ERROR: Invalid file!" << std::endl;
	}
}


Image::Image(std::string fileName)
{
	format = determine_format(fileName);
	init_vectors_256();
	file_name = fileName;
}

Image::~Image()
{
}

void Image::toGrayscale()
{
	
		std::cout << "Converting to graysacle, please wait..." << std::endl;
		Image grayscale_image = *this;
		std::cout << grayscale_image.getImageData().size() << "SIZE" << std::endl;
		int taskSize = grayscale_image.getImageData().size();
		for (int i = 0; i < taskSize; ++i) {
			grayscale_image.image_data[i].toGrayscale();
		}
		grayscale_image.format = PPM;
		grayscale_image.update_raw_data(grayscale_image.format);
		int sub_index = strlen(grayscale_image.file_name.c_str()) - 4;
		std::string newName = grayscale_image.file_name.substr(0, sub_index) + "_grayscale.ppm";
		grayscale_image.setMagicNumber("P6");
		grayscale_image.write_to_file(newName);
}

void Image::toMonochrome()
{
	std::cout << "Converting to monochrome, please wait..." << std::endl;
	Image monochrome_image = *this;
	int taskSize = monochrome_image.image_data.size();
	for (int i = 0; i < taskSize; ++i)
	{
		monochrome_image.image_data[i].toMonochrome();
	}
	monochrome_image.format = PBM;
	monochrome_image.update_raw_data(monochrome_image.format);
	int sub_index = strlen(monochrome_image.file_name.c_str()) - 4;
	std::string newName = monochrome_image.file_name.substr(0, sub_index) + "_monochrome.pbm";
	monochrome_image.setMagicNumber("P6");
	monochrome_image.write_to_file(newName);
}

Image& Image::operator=(const Image& rhs)
{
	if (this != &rhs)
	{
		copy(rhs);
	}
	return *this;
}

Image::Image(const Image& rhs)
{
	copy(rhs);
}
