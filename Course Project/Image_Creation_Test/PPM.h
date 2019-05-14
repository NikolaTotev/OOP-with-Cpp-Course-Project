#pragma once
#include  "RGB.h"
#include <vector>
using std::vector;
using std::string;
class PPM
{
	unsigned int width;
	unsigned int height;
	vector<vector<RGB>> image_data;
	string header;
	string file_name;
	const int max_color_val;
};
