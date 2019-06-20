#include "CommandParser.h"
#include <algorithm>
#include "../Image_Creation_Test/PROTO_Image.h"
#include "Job.h"
#include <thread>


CommandParser::CommandParser()
{
}


CommandParser::~CommandParser()
{
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
					filePaths.push_back(arg);
					newJob->set_path(arg);
					Job* stuff = newJob->copy();
					job_list.push_back(newJob->copy());
					job_created = true;
				}
			
		}
	}
}

void CommandParser::execute_jobs()
{
	vector<thread> jobs;
	for (Job* element : job_list)
	{		
		element->execute();
		//jobs.push_back(thread([=] { element->execute(); }));
	}

	for (int i = 0; i < jobs.size(); ++i)
	{
		//jobs[i].join();
	}	
}

