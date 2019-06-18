#include "Job.h"
#include "Image.h"
#include <iostream>

void Job::gen_final_commands()
{
	for (std::string element : commands)
	{
		if(element.find('=') != std::string::npos)
		{
			std::string arg = element.substr(element.find('=')+1);
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

	for (int i = 0; i < final_commands.size(); ++i)
	{
		if(final_commands[i] == "--monochrome")
		{
			root_image.add_operation(Image::ops::monochrome);
		}
		else if (final_commands[i] == "--grayscale")
		{
			root_image.add_operation(Image::ops::grayscale);
		}
		else if (final_commands[i] =="--histogram")
		{
			std::cout << "Hist" << std::endl;
		}
	}
	root_image.begin_work();
}

Job* Job::copy()
{
	return new Job(*this);	
}
