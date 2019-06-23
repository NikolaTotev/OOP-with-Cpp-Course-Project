#include "Image.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <iterator>

#pragma  region  Initialization functions
///<summary>
///Initializes vectors used for calculating histogram in
///</summary>
///<param>No parameters</param>
///<return>void</return>
void Image::initVectors()
{
	red_count.reserve(256);
	green_count.reserve(256);
	blue_count.reserve(256);

	for (int i = 0; i < 256; ++i)
	{
		red_count.push_back(0);
		green_count.push_back(0);
		blue_count.push_back(0);
	}
}
#pragma  endregion 

#pragma  region  Constructors & redefined operators

Image::Image(std::string fileName)
{
	format = determineFormat(fileName);
	initVectors();
	file_name = fileName;
}

///<summary>
///Equal operator.
///</summary>
///<param name="rhs">const Image&</param>
///<return>Returns Image&</return>
Image& Image::operator=(const Image& rhs)
{
	if (this != &rhs)
	{
		copy(rhs);
	}
	return *this;
}


///<summary>
///Copy constructor.
///</summary>
///<param name="rhs">No parameters</param>
///<return>void</return>
Image::Image(const Image& rhs)
{
	copy(rhs);
}


///<summary>
///Handles copying of the class. Called in the copy constructor. 
///</summary>
///<param name="rhs">Reference to the object that you want to copy.</param>
///<return>void</return>
void Image::copy(const Image& rhs)
{
	file_name = rhs.file_name;
	width = rhs.width;
	height = rhs.height;
	magic_number = rhs.magic_number;
	bitDepth = rhs.bitDepth;
	image_data = rhs.image_data;
	red_count = rhs.red_count;
	green_count = rhs.green_count;
	blue_count = rhs.blue_count;
}
#pragma  endregion 

#pragma  region  Header & image init functions
///<summary>
///Determines the format of the file by reading the last three characters of the fileName argument.
///Accepted args are:
///<para> ppm
///<para> pbm
///<para> pgm
///<para> If none of the above suffixes are found the format is assigned NA.
///</summary>
Image::formats Image::determineFormat(std::string fileName)
{

	int sub_index = strlen(fileName.c_str()) - 3;
	std::string format = fileName.substr(sub_index);

	if (format == "ppm")return PPM;
	if (format == "pgm")return PGM;
	if (format == "pbm")return PBM;
	return NA;
}


///<summary>
///Validates that the header has the correct format. 
///</summary>
///<param name="fileName">A string that is the path that the file should be created at.</param>
///<return>Returns true if the header is valid, otherwise returns false.</return>
bool Image::validHeader(std::string fileName)
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
		set_file_name(fileName);
		set_magic_number(magicNumber);
		set_width(width);
		set_height(height);
		set_bit_depth(bitDepth);
		return true;
	}

	file.close();
	return false;
}

#pragma  endregion 

#pragma  region  Reading image 

///<summary>
///Handles reading the image. Puts read information into pixel format, handles checking if the image in monochrome and graysacle.
///</summary>
///<param name="fileName">A string that is the path that the file should be created at.</param>
///<return>void</return>
void Image::readImage(std::string fileName)
{
	std::cout << "Reading file..." << std::endl;
	std::ifstream file;
	file.open(fileName, std::ios::in | std::ios::ate | std::ios::binary);

	file.unsetf(std::ios::skipws);

	std::streampos size;
	file.seekg(0, std::ios::end);
	size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<char> memBlock(size);

	if (file.is_open())
	{
		memBlock.insert(memBlock.begin(),
			std::istream_iterator<char>(file),
			std::istream_iterator<char>());

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
		unsigned long memSize = memBlock.size();
		unsigned long imageLen = static_cast<unsigned long>(memSize) - headerLength;
		unsigned long modifier = (static_cast<unsigned long>(memSize) - imageLen);
		unsigned long imageSize = imageLen + modifier;
		image_data.reserve(imageSize / 3);
		raw_data.reserve(imageSize);

		int numberOfLoops = 0;
		for (std::streamoff i = headerLength; i < imageSize - 3; i += 3)
		{
			if (i < memBlock.size())
			{
				numberOfLoops++;
				unsigned char R = memBlock[i];
				unsigned char G = memBlock[i + 1];
				unsigned char B = memBlock[i + 2];

				raw_data.push_back(R);
				raw_data.push_back(G);
				raw_data.push_back(B);

				red_count.at(R) += 1;
				blue_count.at(B) += 1;
				green_count.at(G) += 1;

				int avrg = (R + G + B) / 3;
				Pixel pixel(R, G, B, avrg);
				image_data.push_back(pixel);

				if (R != B && B != G && R != G)
				{
					isGrayscale = false;
				}				
			}
		}
		file.close();
	}
}

void Image::updateRawData(formats format)
{
	std::cout << "Updating data... " << std::endl;
	int taskSize = image_data.size();
	int rawDataIndex = 0;

	for (int i = 0; i < taskSize; i++)
	{
		raw_data.push_back(image_data.at(i).getPixel()[0]);

		if (format == PPM || format == PBM)
		{
			raw_data.push_back(image_data.at(i).getPixel()[1]);
			raw_data.push_back(image_data.at(i).getPixel()[2]);
		}
	}
}
#pragma  endregion 

#pragma  region  Writing image
///<summary>
///Creates a new file, then writes all of the relevant information to it. 
///First header info is written, then the raw image data.
///</summary>
///<param name="fileName">A string that is the fileName that the file should be created at.</param>
///<return>void</return>
void Image::writeToFile(std::string fileName) const
{
	std::cout << "Writing to file..." << std::endl;
	std::ofstream file;
	file.open(fileName, std::ios::binary | std::ios::out);
	file << magic_number << std::endl;
	file << width << std::endl << height << std::endl;
	file << bitDepth << std::endl;
	file.write(raw_data.data(), raw_data.size());
	file.close();
}

#pragma  endregion 

#pragma  region  Main program functionality
///<summary>
///Converts image to grayscale by calling the to_grayscale() function on each pixel.
///<seealso cref="Pixel::to_grayscale()">Function for converting a pixel to grayscale.</seealso>
///</summary>
///<param>No parameters</param>
///<return>void</return>
void Image::to_grayscale() const
{
	if (!isGrayscale)
	{
		std::cout << "Converting to graysacle, please wait..." << std::endl;
		Image grayscale_image = *this;
		int taskSize = grayscale_image.image_data.size();
		for (int i = 0; i < taskSize; ++i)
		{
			grayscale_image.image_data[i].toGrayscale();
		}
		grayscale_image.format = PPM;
		grayscale_image.updateRawData(grayscale_image.format);
		int sub_index = strlen(grayscale_image.file_name.c_str()) - 4;
		std::string newName = grayscale_image.file_name.substr(0, sub_index) + "_grayscale.ppm";
		grayscale_image.set_magic_number("P6");
		grayscale_image.writeToFile(newName);
		return;
	}
	std::cout << "No conversion occured, image already grayscale!" << std::endl;
}

///<summary>
///Converts image to monochrome by calling the to_monochrome() function on each pixel.
///<seealso cref="Pixel::to_monochrome()">Function for converting a pixel to monochrome.</seealso>
///</summary>
///<param>No parameters</param>
///<return>void</return>
void Image::to_monochrome()const
{
	if (!isGrayscale)
	{
		std::cout << "Converting to monochrome, please wait..." << std::endl;
		Image monochrome_image = *this;
		int taskSize = monochrome_image.image_data.size();
		for (int i = 0; i < taskSize; ++i)
		{
			monochrome_image.image_data[i].toMonochrome();
		}
		monochrome_image.format = PBM;
		monochrome_image.updateRawData(monochrome_image.format);
		int sub_index = strlen(monochrome_image.file_name.c_str()) - 4;
		std::string newName = monochrome_image.file_name.substr(0, sub_index) + "_monochrome.ppm";
		monochrome_image.set_magic_number("P6");
		monochrome_image.writeToFile(newName);
		return;
	}
	std::cout << "No conversion occured, image already monochrome!" << std::endl;

}

///--monochrome --grayscale --histogram=RED --histogram=BLUE --histogram=GREEN "D:/Documents/Learning/Object Oriented Programming/Course Project/OOP-Course-Project-S1/saves/Lenna_512.ppm" --monochrome --grayscale --histogram=RED --histogram=BLUE --histogram=GREEN "D:/Documents/Learning/Object Oriented Programming/Course Project/OOP-Course-Project-S1/saves/other.ppm" 
///<summary>
///Generates histogram from image data.
///</summary>
///<param>No parameters</param>
///<return>void</return>
void Image::gen_histogram(Job::args_enum target_color) const
{


	std::cout << "Generating histogram ";

	///Percentage vectors - they hold the information about the percentages of each color.
	std::vector<float> red_percent;
	std::vector<float> green_percent;
	std::vector<float> blue_percent;

	red_percent.reserve(256);
	green_percent.reserve(256);
	blue_percent.reserve(256);

	for (int i = 0; i < 256; ++i)
	{
		red_percent.push_back(0);
		green_percent.push_back(0);
		blue_percent.push_back(0);
	}
	for (int i = 0; i < 256; ++i)
	{
		red_percent.at(i) = (getReds().at(i) / (height * width)) * 100;
		green_percent.at(i) = (getGreens().at(i) / (height * width)) * 100;
		blue_percent.at(i) = (getBlues().at(i) / (height * width)) * 100;
	}

	///Vector that holds all of the information for the histogram image.
	std::vector<std::vector<Pixel>> histogramData;
	histogramData.reserve(256);

	std::vector<Pixel> backgroundCol;
	backgroundCol.reserve(100);

	///Populating background color vector.
	for (int i = 0; i < 100; ++i)
	{
		backgroundCol.push_back(Pixel(15, 15, 15, 1));
	}

	///Setting background color of the histogram.
	for (int y = 0; y < 256; ++y)
	{
		histogramData.push_back(backgroundCol);
	}

	///Vector that stores the percentages of the desired color.
	std::vector<float> target_percentages;

	///Color that will be used to display the histogram data.
	Pixel color;

	///Suffix, added at the end of the name of the produced file.
	std::string suffix;

	///Determining what settings to be applied in order to graph the histogram of the given color. 
	switch (target_color) {
	case Job::RED:
		target_percentages = red_percent;
		color.setPixel(255, 1, 1, 1);
		suffix = "_histogram_red.ppm";
		std::cout << "for reds." << std::endl;
		break;
	case Job::GREEN:
		target_percentages = green_percent;
		color.setPixel(1, 255, 1, 1);
		suffix = "_histogram_green.ppm";
		std::cout << "for greens." << std::endl;
		break;
	case Job::BLUE:
		target_percentages = blue_percent;
		color.setPixel(1, 1, 255, 1);
		suffix = "_histogram_blue.ppm";
		std::cout << "for blues." << std::endl;
		break;
	case Job::NA:
		std::cout << "Failed to generate histogram, missing or invalid arguments!" << std::endl;
		break;
	default:;
	}

	///Loop for graphing histogram
	for (int i = 0; i < 256; i++)
	{
		for (int j = 98; j > abs(98 - target_percentages[i]); --j)
		{
			histogramData[i][j] = color;
		}
	}

	///Loop for drawing horizontal axis.
	for (int i = 0; i < 256; ++i)
	{
		histogramData[i][99] = Pixel(255, 186, 1, 1);
	}

	///Loop for drawing vertical axis.
	for (int i = 0; i < 100; ++i)
	{
		histogramData[0][i] = Pixel(255, 186, 1, 1);
	}

	int sub_index = strlen(file_name.c_str()) - 4;
	std::string mainPath = file_name.substr(0, sub_index) + suffix;
	char* rawData = new char[100 * 256 * 3];
	int rawIndex = 0;


	std::ofstream file;
	file.open(mainPath, std::ios::binary | std::ios::out);

	///Setting header of the image
	file << "P6" << std::endl;
	file << 256 << std::endl << 100 << std::endl;
	file << "255" << std::endl;

	///Converting pixel data to raw data.
	for (int y = 0; y < 100; ++y)
	{
		for (int x = 0; x < 256; ++x)
		{
			rawData[rawIndex] = histogramData[x][y].getPixel()[0];
			rawData[rawIndex + 1] = histogramData[x][y].getPixel()[1];
			rawData[rawIndex + 2] = histogramData[x][y].getPixel()[2];

			rawIndex += 3;
		}
	}

	///Writing to file.
	file.write(rawData, strlen(rawData));
	file.close();
	delete[] rawData;
}
#pragma  endregion 

#pragma  region  Operation execution
///<summary>
/// Adds operation to the list of operations to be performed on the image.
///</summary>
///<param name="op">Operation to be added</param>
///<param name="args">Argument for the function being added. Default value is "no_args"</param>
///<return>void</return>
void Image::add_operation(ops op, Job::args_enum args)
{
	operations.push_back(op);
	op_args.push_back(args);
}

///<summary>
///Handles operation execution. 
///Each operation is launched on a separate thread for better performance
///</summary>
///<param>No parameters</param>
///<return>void</return>
void Image::executeTasks() const
{
	std::vector<std::thread> tasks;
	for (int i = 0; i < operations.size(); ++i)
	{
		if (operations[i] == monochrome)
		{
			to_monochrome();
		}
		if (operations[i] == grayscale)
		{
			to_grayscale();

		}
		if (operations[i] == histogram)
		{
			gen_histogram(op_args[i]);
		}
	}
}

///<summary>
///Checks if file_name is valid. If it is commands for operation execution are run,
///if file path is not valid error message is displayed on the console.
///</summary>
///<param>No parameters</param>
///<return>void</return>
void Image::begin_work()
{
	if (validHeader(file_name))
	{
		readImage(file_name);
		executeTasks();
	}
	else
	{
		std::cout << "ERROR: Invalid file!" << std::endl;
	}
}
#pragma  endregion 
