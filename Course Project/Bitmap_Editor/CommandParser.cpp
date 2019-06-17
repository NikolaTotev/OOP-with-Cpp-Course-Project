#include "CommandParser.h"
#include <algorithm>
#include "../Image_Creation_Test/PROTO_Image.h"


CommandParser::CommandParser()
{
}


CommandParser::~CommandParser()
{
}

void CommandParser::parse_input(int argc, char *input[])
{
	if (argc > 2)
	{

		for (int i = 1; i < argc; ++i)
		{
			string arg = input[i];
			
			if (arg.length() > 2 && arg[0] == '-' && arg.at(1) == '-')
				{
					raw_commands.push_back(arg);
	
				}
				else
				{
					filePaths.push_back(arg);
				}
			
		}
	}

	if(valid_commands())
	{
		gen_jobs();
	}
}

bool CommandParser::valid_commands()
{
	for (string element : raw_commands)
	{
		if(acceptedCommands.count(element)==0)
		{
			cout << element << "ELEMENT" << endl;
			cout << acceptedCommands.count(element) << "ELEMENT COUNT" << endl;

			return false;
		}
	}
	return true;
}

void CommandParser::gen_jobs()
{
	
}
