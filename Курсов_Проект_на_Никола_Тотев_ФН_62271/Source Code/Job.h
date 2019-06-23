#pragma once
#include <vector>
#include <string>
#include <set>

class Job
{
	const std::set<std::string> allowed_args = { "RED", "GREEN", "BLUE" };
	std::vector<std::string> commands;
	std::vector<std::string>final_commands;
	std::vector<std::string>command_args;
	std::string path;
public:

	///Arguments for histogram function. If no color is given NA is applied.
	enum args_enum { RED, GREEN, BLUE, NA};

	///Create the final list of operations along with the corresponding arguments.
	void gen_final_commands();

	///Add commands to the list of commands.
	void add_command(std::string cmd);

	///Setter for the target path of the job.
	void set_path(std::string _path);

	///Command for executing all of the operations.
	void execute();

	Job* copy();
};

