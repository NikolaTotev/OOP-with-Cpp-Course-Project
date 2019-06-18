#pragma once
#include <vector>
#include <string>
#include <map>

class Job
{
public:
	std::vector<std::string> commands;
	std::vector<std::string>final_commands;
	std::vector<std::string>command_args;
	std::string path;
	void gen_final_commands();
	

	void add_command(std::string cmd);
	void set_path(std::string _path);
	void execute();
	Job* copy();
};

