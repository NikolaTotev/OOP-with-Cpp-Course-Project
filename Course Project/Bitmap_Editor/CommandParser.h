#pragma once
#include  <string>
#include <vector>
#include <iostream>
using namespace std;
class CommandParser
{
	enum  states {seek_cmnd, seek_path, read_cmd, read_path};
	states currentState = seek_cmnd;
public:
	CommandParser();
	~CommandParser();
	std::vector<std::string> commands;
	std::vector<std::string> filePaths;
	std::string command_start = "-";
	string temp_cmnd="";
	string temp_path="";
	void separate_input(int argc, char *input[]);
	bool valid_command();
};

