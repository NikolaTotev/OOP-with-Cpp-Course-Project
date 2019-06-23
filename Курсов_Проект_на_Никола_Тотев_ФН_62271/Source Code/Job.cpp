#include "Job.h"
#include "Image.h"
#include <iostream>

void Job::gen_final_commands()
{
	for (std::string element : commands)
	{
		if (element.find('=') != std::string::npos)
		{
			std::string arg = element.substr(element.find('=') + 1);
			final_commands.push_back(element);
			command_args.push_back(arg);
		}
		else
		{
			final_commands.push_back(element);
			command_args.push_back("no_arg");
		}
	}
}

void Job::add_command(std::string cmd)
{
	commands.push_back(cmd);
}

void Job::set_path(std::string _path)
{
	path = _path;
}

void Job::execute() 
{
	gen_final_commands();
	Image root_image(path);
	std::cout << std::endl;
	std::cout << "Working on: " << path << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < final_commands.size(); ++i)
	{
		if (final_commands[i] == "--monochrome")
		{
			root_image.add_operation(Image::ops::monochrome);
		}
		else if (final_commands[i] == "--grayscale")
		{
			root_image.add_operation(Image::ops::grayscale);
		}
		else if (final_commands[i].substr(0, 11 ) == "--histogram")
		{
			if (allowed_args.count(command_args[i]) != 0)
			{

				if (command_args[i] == "RED")
				{
					root_image.add_operation(Image::ops::histogram, RED);
				}
				else if (command_args[i] == "BLUE")
				{
					root_image.add_operation(Image::ops::histogram, BLUE);
				}
				else if (command_args[i] == "GREEN")
				{
					root_image.add_operation(Image::ops::histogram, GREEN);
				}
			}
			else
			{
				std::cout << "Histogram command has wrong or missing arguments!" << std::endl;
				return;
			}
		}
	}
	root_image.begin_work();
}

Job* Job::copy()
{
	return new Job(*this);
}
