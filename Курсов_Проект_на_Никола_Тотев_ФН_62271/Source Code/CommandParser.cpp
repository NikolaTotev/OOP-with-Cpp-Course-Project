#include "CommandParser.h"
#include <algorithm>
#include "Job.h"
#include <thread>
#include <filesystem>
namespace fs = experimental::filesystem;

CommandParser::~CommandParser()
{
	for (int i = 0; i < job_list.size(); ++i)
	{
		delete job_list[i];
	}
}

void CommandParser::parse_input(int argc, char *input[])
{
	bool job_created = false;
	Job* newJob = new Job;

	if (argc > 2)
	{

		for (int i = 1; i < argc; ++i)
		{
			string arg = input[i];
			if(job_created)
			{
			newJob = new Job;
			job_created = false;
			}
			if (arg.length() > 2 && arg[0] == '-' && arg.at(1) == '-')
				{

					if(acceptedCommands.count(arg) != 0)
					{
						raw_commands.push_back(arg);
						newJob->add_command(arg);
					}
					else
					{
						return;
					}					
				}
				else
				{
					if(arg.substr(0, 1) == ".")
					{
						string rel_path = fs::current_path().string();					
					}
					filePaths.push_back(arg);
					newJob->set_path(arg);					
					job_list.push_back(newJob->copy());
					job_created = true;
				}
			
		}
	}
}

void CommandParser::execute_jobs()const
{
	for (Job* element : job_list)
	{				
		element->execute();
	}	
}

