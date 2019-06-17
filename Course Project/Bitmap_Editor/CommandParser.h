#pragma once
#include  <string>
#include <vector>
#include <iostream>
#include <set>

using namespace std;
class CommandParser
{
	enum  states {seek_cmnd, seek_path, read_cmd, read_path};
	states currentState = seek_cmnd;
	set<string> acceptedCommands = { "--monochrome", "--grayscale", "--histogram=RED","--histogram=GREEN", "--histogram=BLUE" };
public:
	CommandParser();
	~CommandParser();
	std::vector<std::string> raw_commands;
	std::vector<std::string> filePaths;
	std::string command_start = "-";
	string temp_cmnd="";
	string temp_path="";
	void parse_input(int argc, char *input[]);
	bool valid_commands();
};

