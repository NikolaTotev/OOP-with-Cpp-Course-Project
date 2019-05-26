#include "CommandParser.h"



CommandParser::CommandParser()
{
}


CommandParser::~CommandParser()
{
}

void CommandParser::separate_input(int argc, char *input[])
{
	if (argc > 2)
	{

		for (int i = 1; i < argc; ++i)
		{
			string arg = input[i];
			
			if (arg.length() > 2 && arg[0] == '-' && arg.at(1) == '-')
				{
					commands.push_back(arg);
	
				}
				else
				{
					filePaths.push_back(arg);
				}
			
		}
	}
}
