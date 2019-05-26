#include "CommandParser.h"



CommandParser::CommandParser()
{
}


CommandParser::~CommandParser()
{
}

void CommandParser::separate_input(std::string input)
{
	input += " ";
	char space = ' ';
	char dash = '-';
	int dashCounter=0;
	for (int i = 0; i < input.length(); ++i)
	{
		switch (currentState) {
		case seek_cmnd:

			if (input.at(i) == dash)
			{
				dashCounter += 1;
				if(dashCounter == 2)
				{
				currentState = read_cmd;
				dashCounter = 0;
				}
			}
			break;
		case read_cmd:
			if(input.at(i) != space)
			{
				if(input.at(i)!= dash)
				{				
					temp_cmnd += input.at(i);
				}
				
			}
			else
			{
				if(!valid_command())
				{
					cout << "Invalid command" << endl;
					break;								
				}
				currentState = read_path;
			}
			break;
		case seek_path:
			break;
		case read_path:			
			if (input.at(i) != space)
			{
				temp_path += input.at(i);
			}
			else
 			{	
				if(!temp_path.empty())
				{
					filePaths.push_back(temp_path);
					temp_path = "";
					if(i != input.size())
					{
						currentState = seek_cmnd;
					}
				}
				
			}
			break;
		default:;
		}
	}
}

bool CommandParser::valid_command()
{
	if(temp_cmnd == "tmpCmd" || temp_cmnd =="other")
	{
		commands.push_back(temp_cmnd);
		temp_cmnd = "";
		return true;
	}
}
