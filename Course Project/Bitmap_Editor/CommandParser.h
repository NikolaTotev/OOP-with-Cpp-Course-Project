#pragma once
#include  <string>
#include <vector>
#include <iostream>
#include <set>
#include "Job.h"

using namespace std;
class CommandParser
{
	///Set of commands that are accepted by the application. Used to check the input.
	set<string> acceptedCommands = { "--monochrome", "--grayscale", "--histogram=RED","--histogram=GREEN", "--histogram=BLUE" };
	
	///Command start identifier.
	std::string command_start = "-";

	std::vector<std::string> raw_commands;
	std::vector<std::string> filePaths;

	///List of jobs. One job per path found.
	vector<Job*> job_list;

public:
	///Destructor
	~CommandParser();

	///Main operations
	void parse_input(int argc, char *input[]);
	void execute_jobs() const;
};

